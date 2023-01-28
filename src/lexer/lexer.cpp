#include "lexer.hpp"

#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "../debug/log.hpp"
#include "../exception/syntax_error.hpp"
#include "../token/token_type_helpers.hpp"


// TokenStream handling:
auto Lexer::add_token(Token&& t_token) -> void
{
  m_tokenstream.push_back(std::forward<Token>(t_token));
}

// Error handling:
auto Lexer::syntax_error(std::string_view t_msg) const -> void
{
  // FIXME: The ^^^ does not properly align, columnno is possibly not
  // properly adjusted

  // Throws a SyntaxError with a message
  throw SyntaxError{std::string{t_msg}, m_filebuffer.path().string(),
                    m_filebuffer.lineno(), m_filebuffer.line(),
                    m_filebuffer.columnno()};
}

// Public constructors:
Lexer::Lexer(FileBuffer& t_filebuffer): m_filebuffer{t_filebuffer}
{}

// Public methods:
auto Lexer::is_keyword(std::string_view t_identifier) -> TokenType
{
  using namespace reserved::keywords;

  // TODO: Clean this up we could use a loop with an std::pair for the tokentype
  // Having a centralized location for
  for(auto keyword : g_keywords)
    if(t_identifier == keyword.identifier())
      return TokenType{keyword};

  return TokenType::NONE;
}

auto Lexer::identifier() -> Token
{
  Token token;
  std::stringstream ss;

  auto is_valid_character{[&](const char t_char) -> bool {
    return std::isalnum(t_char) || t_char == '_';
  }};

  while(is_valid_character(m_filebuffer.character()) && !eol())
    ss << next_char();

  // We go back one since we add till we find a character that does not
  // Match so we have to unget it
  m_filebuffer.backward();

  // Verify if it is a keyword or not
  if(const auto tokentype{is_keyword(ss.str())}; tokentype != TokenType::NONE)
    token = Token{tokentype};
  else
    token = Token{TokenType::IDENTIFIER, ss.str()};

  LOG(LogLevel::INFO, "IDENTIFIER: ", ss.str());
  return token;
}

// Helper functions for literal_numeric
auto Lexer::is_hex_literal() -> bool
{
  // Octal literals are not specified in the POSIX AWK standard
  // So just treat leading zeroes as as normal
  if(next_char() == '0' && m_filebuffer.character() == 'x') {
    next_char(); // Discard 'x'

    return true;
  } else {
    // If we just have a zero we should go back to not discard the zero
    m_filebuffer.backward();
  }

  return false;
}

auto Lexer::handle_hex() -> Token
{
  std::stringstream ss;

  while(!eol()) {
    const char character{m_filebuffer.character()};

    if(std::isxdigit(character)) {
      ss << next_char();
    } else {
      m_filebuffer.backward();
      break;
    }
  }

  LOG(LogLevel::INFO, "HEX: ", ss.str());
  const int number{(int)std::stoul(ss.str(), nullptr, 16)};

  return Token{TokenType::HEX, number};
}

// t_str and t_dot have default arguments
// t_str contains is for if you already have part of a string to continue on
// t_dot indicates if there is already a dot in the string
auto Lexer::handle_float(std::string_view t_str, bool t_dot) -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  ss << t_str;

  if(t_dot)
    next_char();

  while(!eol()) {
    const char character{m_filebuffer.character()};

    if(std::isdigit(character)) {
      ss << next_char();
    } else if(character == g_dot.identifier()) {
      if(t_dot) {
        syntax_error("Cant have a second '.' in a float literal.");
      } else {
        t_dot = true;
      }
    } else {
      m_filebuffer.backward();
      break;
    }
  }

  LOG(LogLevel::INFO, "FLOAT: ", ss.str());
  return Token{TokenType::FLOAT, std::stod(ss.str())};
}

auto Lexer::handle_integer() -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  while(!eol()) {
    const char character{m_filebuffer.character()};

    if(std::isdigit(character)) {
      ss << next_char();
    } else if(character == g_dot.identifier()) {
      // Handle float as a float
      return handle_float(ss.str(), true);
    } else {
      m_filebuffer.backward();
      break;
    }
  }

  LOG(LogLevel::INFO, "INTEGER: ", ss.str());
  return Token{TokenType::INTEGER, (int)std::stoi(ss.str())};
}

// TODO: Split int, hex and float part into separate functions
auto Lexer::literal_numeric() -> Token
{
  // Just forward to the apropiate numeric literal handle function
  if(is_hex_literal()) {
    return handle_hex();
  } else {
    // handle_integer() may also forward to handle_float()
    return handle_integer();
  }
}

auto Lexer::literal_string() -> Token
{
  using namespace reserved::symbols::none;

  std::stringstream ss;

  // Discard starting " character
  next_char();

  bool quit{false};
  while(!quit && !eol()) {
    const char character{m_filebuffer.character()};

    switch(character) {
      case g_double_quote.identifier():
        quit = true;
        break;

      case g_backslash.identifier():
        ss << next_char();
        [[fallthrough]];

      default:
        ss << next_char();
        break;
    }
  }

  LOG(LogLevel::INFO, "STRING: ", '"', ss.str(), '"');
  return Token{TokenType::STRING, ss.str()};
}

auto Lexer::literal_regex() -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  // Discard starting / character
  next_char();

  // TODO: As of now regex literals perform no checks if the identifier in
  // front of the literal has an integer type or not, as of now we just assume
  // it is a regex expression we should also throw an error or assume a
  // division if we do not find a corresponding / before the EOL
  bool quit{false};
  while(!quit && !eol()) {
    const char character{m_filebuffer.character()};

    switch(character) {
      case g_slash.identifier():
        quit = true;
        break;

      case g_newline.identifier():
        // FIXME: Error on regex literals not being closed on the same line
        // For now just end REGEX on new line
        quit = true;
        break;

        // TODO: Take care of handling octal escape codes and other
      case none::g_backslash.identifier():
        ss << next_char();
        [[fallthrough]];

      default:
        ss << next_char();
        break;
    }
  }

  LOG(LogLevel::INFO, "REGEX: ", ss.str());
  return Token{TokenType::REGEX, ss.str()};
}

auto Lexer::is_multi_symbol() -> TokenType
{
  using namespace reserved::symbols;

  std::stringstream ss;
  TokenType tokentype{TokenType::NONE};
  const char character{m_filebuffer.character()};

  ss << character;

  // TODO: We use two loops now, we can change this to only use one
  // Refactor someday
  for(const auto multi : g_multi_symbols)
    if(character == multi.identifier().front()) {
      next_char();
      ss << m_filebuffer.character();

      if(!eol())
        for(const auto multi : g_multi_symbols)
          if(ss.str() == multi.identifier()) {
            tokentype = TokenType{multi};

            LOG(LogLevel::INFO, "MULTI SYMBOL: ", ss.str());
            break; // We found a multi symbol token!
          }

      // If the next character is not part of
      // A multi symbol just undo the forward
      if(tokentype == TokenType::NONE)
        m_filebuffer.backward();

      // We compare against all reserverd multi symbols in the second loop
      // So there is no need to iterate againt after we found our first match
      break;
    }

  return tokentype;
}

auto Lexer::is_single_symbol() -> TokenType
{
  using namespace reserved::symbols;

  const char character{m_filebuffer.character()};
  TokenType tokentype{TokenType::NONE};

  for(const auto single : g_single_symbols)
    if(character == single.identifier()) {
      tokentype = TokenType{single};
      LOG(LogLevel::INFO, "SINGLE SYMBOL: ", character);
      break;
    }

  return tokentype;
}

auto Lexer::symbol() -> Token
{
  TokenType tokentype{TokenType::NONE};

  // First check for multi symbol
  tokentype = is_multi_symbol();

  // Then check for single symbol
  if(tokentype == TokenType::NONE)
    tokentype = is_single_symbol();

  // Throw if it is neither
  if(tokentype == TokenType::NONE) {
    std::cout << "Token Error: " << m_filebuffer.character() << '\n';
    syntax_error("Character encountered is not valid AWX!");
  }

  // Add the symbol if we recognize it
  return Token{tokentype};
}

auto Lexer::next_char() const -> char
{
  return m_filebuffer.forward();
}

auto Lexer::eol() const -> bool
{
  return m_filebuffer.eol();
}

auto Lexer::tokenize() -> TokenStream
{
  using namespace reserved::symbols;

  LOG_PRINT("=== LEXING ===");

  constexpr char double_quote{none::g_double_quote.identifier()};
  constexpr char slash{g_slash.identifier()};

  for(; !m_filebuffer.eof(); m_filebuffer.next())
    while(!eol()) {
      const char character{m_filebuffer.character()};

      const TokenType last_tokentype{m_tokenstream.back().type()};

      // TODO: String concatenation is not lexed right now
      if(std::isspace(character)) {
        // Just ignore whitespace, but do not ignore newlines
        if(character == g_newline.identifier()) {
          LOG(LogLevel::INFO, "NEWLINE");
          add_token(Token{TokenType::NEWLINE});
        }
      } else if(character == '#') { // # Denotes comments
        // Stop lexing the current line and continue with the next!
        break;
      } else if(std::isalpha(character)) {
        add_token(identifier());
      } else if(std::isdigit(character)) {
        add_token(literal_numeric());
      } else if(character == double_quote)
        add_token(literal_string());
      else if(character == slash && !tokentype::is_int(last_tokentype))
        add_token(literal_regex());
      else
        add_token(symbol());

      // Increment at the end, this allows us to prevent having to use
      // m_filebuffer.backward() in situations where we look a head to much
      m_filebuffer.forward();
    }

  LOG_PRINT();
  return m_tokenstream;
}

Lexer::~Lexer()
{}
