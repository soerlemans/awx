#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "../exception.hpp"
#include "../log.hpp"

#include "lexer.hpp"
#include "reserved.hpp"
#include "tokentype.hpp"


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
{
  m_tokenstream.reserve(256);
}

// Public methods:
auto Lexer::is_keyword(std::string_view t_identifier) -> TokenType
{
  using namespace reserved::keywords;

  // TODO: Clean this up we could use a loop with an std::pair for the tokentype
  // Having a centralized location for
  for(auto keyword : g_keywords)
    if(t_identifier == keyword.identifier())
      return keyword.tokentype();

  return TokenType::UNKNOWN;
}

auto Lexer::identifier() -> Token
{
  Token token;
  std::stringstream ss;

  auto is_valid_character{[&](const char t_char) -> bool {
    return std::isalnum(t_char) || t_char == '_';
  }};

  while(is_valid_character(m_filebuffer.character()) && !m_filebuffer.eol())
    ss << m_filebuffer.forward();

  // Verify if it is a keyword or not
  if(const auto tokentype{is_keyword(ss.str())};
     tokentype != TokenType::UNKNOWN)
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
  // So just discard leading zeros
  if(m_filebuffer.character() == '0')
    {
      // TODO: Define reserved hex literal symbol
      // If the next character is a 'x' it must be a hex literal
      m_filebuffer.forward();
      if(m_filebuffer.character() == 'x')
        {
          m_filebuffer.forward();

          return true;
      }
  }

  return false;
}

auto Lexer::literal_numeric() -> Token
{
  using namespace reserved::symbols;

  Token token;

  bool hex{is_hex_literal()};
  bool is_float{false};

  std::stringstream ss;
  while(!m_filebuffer.eol())
    {
      const char character{m_filebuffer.character()};

      // is_valid_character for different type of integer literals
      if(std::isdigit(character))
        {
          ss << m_filebuffer.forward();
      } else if(hex && std::isxdigit(character))
        {
          // The following check is probably not needed, but implement it one
          // day just in case to be sure
          // if(is_float)
          //   syntax_error("Illegal character in ");

          ss << m_filebuffer.forward();
      } else if(!is_float && character == g_dot.identifier())
        {
          // Cant be a hex literal with a floating point at the same time in
          // the future we might have primitive types be classes ruby style so
          // someday this could be a feature But for now give an error on this
          if(hex)
            syntax_error("Found a . in a hex literal");

          is_float = true;
          ss << m_filebuffer.forward();
      } else
        { // Quit if digit ends
          break;
        }
    }

  // Determine what must be returned:
  if(hex)
    token = Token{TokenType::HEX, ss.str()};
  else if(is_float)
    token = Token{TokenType::FLOAT, std::stod(ss.str())};
  else
    token = Token{TokenType::INTEGER, ss.str()};

  LOG(LogLevel::INFO, "NUMERIC: ", ss.str());
  return token;
}

auto Lexer::literal_string() -> Token
{
  using namespace reserved::symbols::none;

  std::stringstream ss;

  // Discard starting " character
  m_filebuffer.forward();

  bool quit{false};
  while(!quit && !m_filebuffer.eol())
    {
      const char character{m_filebuffer.character()};

      switch(character)
        {
          case g_double_quote.identifier():
            quit = true;
            break;

          case g_backslash.identifier():
            ss << m_filebuffer.forward();
            [[fallthrough]];

          default:
            ss << m_filebuffer.forward();
            break;
        }
    }

  LOG(LogLevel::INFO, "STRING: ", ss.str());
  return Token{TokenType::STRING, ss.str()};
}

auto Lexer::literal_regex() -> Token
{
  using namespace reserved::symbols;

  std::stringstream ss;

  // Discard starting / character
  m_filebuffer.forward();

  // TODO: As of now regex literals perform no checks if the identifier in front
  // of the literal has an integer type or not, as of now we just assume it is a
  // regex expression we should also throw an error or assume a division if we
  // do not find a corresponding / before the EOL
  bool quit{false};
  while(!quit && !m_filebuffer.eol())
    {
      const char character{m_filebuffer.character()};

      switch(character)
        {
          case g_slash.identifier():
            quit = true;
            break;

            // TODO: Take care of handling octal escape codes and other
          case none::g_backslash.identifier():
            ss << m_filebuffer.forward();
            [[fallthrough]];

          default:
            ss << m_filebuffer.forward();
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
  TokenType tokentype{TokenType::UNKNOWN};
  const char character{m_filebuffer.character()};

  ss << character;

  // TODO: We use two loops now, we can change this to only use one
  // Refactor someday
  for(const auto multi : g_multi_symbols)
    if(character == multi.identifier().front())
      {
        m_filebuffer.forward();
        ss << m_filebuffer.character();

        if(!m_filebuffer.eol())
          for(const auto multi : g_multi_symbols)
            if(ss.str() == multi.identifier())
              {
                tokentype = multi.tokentype();

				LOG(LogLevel::INFO, "MULTI SYMBOL: ", ss.str());
                break; // We found a multi symbol token!
            }

        // If the next character is not part of
        // A multi symbol just undo the forward
        if(tokentype == TokenType::UNKNOWN)
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
  TokenType tokentype{TokenType::UNKNOWN};

  for(const auto single : g_single_symbols)
    if(character == single.identifier())
      {
        tokentype = single.tokentype();
		LOG(LogLevel::INFO, "SINGLE SYMBOL: ", character);
        break;
    }

  return tokentype;
}

auto Lexer::symbol() -> Token
{
  TokenType tokentype{TokenType::UNKNOWN};

  // First check for multi symbol
  tokentype = is_multi_symbol();

  // Then check for single symbol
  if(tokentype == TokenType::UNKNOWN)
    tokentype = is_single_symbol();

  // Throw if it is neither
  if(tokentype == TokenType::UNKNOWN)
    {
      std::cout << "Token Error: " << m_filebuffer.character() << '\n';
      syntax_error("Character encountered is not valid AWX!");
  }

  // Add the symbol if we recognize it
  return Token{tokentype};
}

auto Lexer::tokenize() -> TokenStream
{
  using namespace reserved::symbols;

  constexpr char double_quote{none::g_double_quote.identifier()};
  constexpr char slash{g_slash.identifier()};

  const TokenType last_tokentype{m_tokenstream.back().type()};

  for(; !m_filebuffer.eof(); m_filebuffer.next())
    while(!m_filebuffer.eol())
      {
        const char character{m_filebuffer.character()};

        if(std::isspace(character))
          ;                       // Just ignore whitespace
        else if(character == '#') // # Denotes comments
          break;                  // Stop parsing current line
        else if(std::isalpha(character))
          {
            add_token(identifier());
            continue;
        } else if(std::isdigit(character))
          {
            add_token(literal_numeric());
            continue;
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

  return m_tokenstream;
}

Lexer::~Lexer()
{}
