#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "exception.hpp"
#include "reserved.hpp"
#include "tokenizer.hpp"
#include "tokentype.hpp"


// TokenStream handling:
auto Tokenizer::add_token(const Token&& t_token) -> void
{
  m_tokenstream.push_back(t_token);
}

// Error handling:
auto Tokenizer::syntax_error(std::string_view t_msg) const -> void
{
  // FIXME: The ^^^ does not properly align, columnno is possibly not
  // properly adjusted

  // Throws a SyntaxError with a message
  throw SyntaxError{std::string{t_msg}, m_filebuffer.path().string(),
					m_filebuffer.lineno(), m_filebuffer.line(),
                    m_filebuffer.columnno()};
}

// Helper functions for literal_numeric
auto Tokenizer::check_hex() -> bool
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

auto Tokenizer::literal_numeric() -> void
{
  using namespace reserved::symbols;

  // TODO: Make separate function for handling floats
  bool is_hex{check_hex()};
  bool is_float{false};

  std::stringstream ss;
  while(!m_filebuffer.eol())
    {
      const char character{m_filebuffer.character()};

      // Check for different type of integer literals
      if(std::isdigit(character)) {
          ss << m_filebuffer.forward();
	  }else if(is_hex && std::isxdigit(character)) {
          // The following check is probably not needed, but implement it one
          // day just in case to be sure
		  // if(is_float)
          //   syntax_error("Illegal character in ");

          ss << m_filebuffer.forward();
      }else if(!is_float && character == g_dot.identifier()) {
          // Cant be a is_hex literal with a floating point at the same time in
          // the future we might have primitive types be classes ruby style so
          // someday this could be a feature But for now give an error on this
          if(is_hex)
            syntax_error("Found a . in a hex literal");

          is_float = true;
          ss << m_filebuffer.forward();
      }else{ // Quit if digit ends
          break;
        }
    }

  if(is_hex) {
	add_token(Token{TokenType::HEX, ss.str()});
	std::cout << "Hex: " << ss.str() << '\n';
  }else if(is_float) {
	add_token(Token{TokenType::FLOAT, std::stod(ss.str())});
	std::cout << "Float: " << ss.str() << '\n';
  }else{
	add_token(Token{TokenType::INTEGER, ss.str()});
	std::cout << "Integer: " << ss.str() << '\n';
  }
}

auto Tokenizer::literal_string() -> void
{
  using namespace reserved::symbols::none;

  std::stringstream ss;

  // Discard starting " character
  m_filebuffer.forward();

  bool quit{false};
  while(!quit && !m_filebuffer.eol())
	{
	  const char character{m_filebuffer.character()};

	  switch(character) {
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

  add_token(Token{TokenType::STRING, ss.str()});
  std::cout << "String: " << ss.str() << '\n';
}

auto Tokenizer::is_keyword(std::string_view t_identifier) -> TokenType
{
  using namespace reserved::keywords;

  // TODO: Clean this up we could use a loop with an std::pair for the tokentype
  // Having a centralized location for
  for(auto keyword : g_keywords)
    if(t_identifier == keyword.identifier())
      return keyword.tokentype();

  return TokenType::UNKNOWN;
}

auto Tokenizer::identifier() -> void
{
  std::stringstream ss;
  while(std::isalnum(m_filebuffer.character()) && !m_filebuffer.eol())
    ss << m_filebuffer.forward();

  // Verify if it is a keyword or not
  if(const auto token_type{is_keyword(ss.str())};
	 token_type != TokenType::UNKNOWN) {
	add_token(Token{token_type});
	std::cout << "Keyword: " << ss.str() << std::endl;
  }else{
	add_token(Token{TokenType::IDENTIFIER, ss.str()});
	std::cout << "Identifier: " << ss.str() << std::endl;
  }
}

auto Tokenizer::literal_operator() -> void
{
  using namespace reserved::symbols;

  // TODO: Check single symbols first if there is a multi symbols variant check
  // If the next character corresponds, if we find nothing that it could be give
  // A syntax error

  std::stringstream ss;
  const auto character{m_filebuffer.character()};
  TokenType tokentype{TokenType::UNKNOWN};
  for(const auto single : g_single_symbols)
	if(character == single.identifier())
	  tokentype = single.tokentype();

  ss << character << m_filebuffer.forward();

  if(tokentype != TokenType::UNKNOWN && !m_filebuffer.eol())
	{
	  for(const auto multi : g_multi_symbols)
		if(ss.str() == multi.identifier())
		  {
			add_token(Token{multi.tokentype()});
			std::cout << "Multi symbol: " << ss.str() << '\n';
		  }
	}else{
	add_token(Token{tokentype});
	std::cout << "Single symbol: " << character << '\n';
  }
}

// Public constructors:
Tokenizer::Tokenizer(FileBuffer &t_filebuffer): m_filebuffer{t_filebuffer}
{
  m_tokenstream.reserve(256);
}

// Public methods:
auto Tokenizer::tokenize() -> TokenStream
{
  using namespace reserved::symbols::none;

  for(; !m_filebuffer.eof(); m_filebuffer.next())
    for(; !m_filebuffer.eol(); m_filebuffer.forward())
      {
        const char character{m_filebuffer.character()};

        if(std::isalpha(character))
          identifier();
        else if(std::isdigit(character))
          literal_numeric();
        else if(character == g_double_quote.identifier())
		  literal_string();
		else
		  literal_operator();
      }

  return m_tokenstream;
}

Tokenizer::~Tokenizer()
{}
