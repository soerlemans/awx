#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "exception.hpp"
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
auto Tokenizer::is_hex() -> bool
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

// auto Tokenizer::is_float() -> bool
// {}

auto Tokenizer::literal_numeric() -> void
{
  using namespace reserved::symbols;

  // TODO: Make separate function for handling floats
  bool hex{is_hex()};
  bool is_float{false};

  std::stringstream ss;
  while(!m_filebuffer.eol())
    {
      const char character{m_filebuffer.character()};

      // Check for integer
      if(std::isdigit(character)) {
          ss << m_filebuffer.forward();

          // Check for floating point
      }else if(!is_float && character == g_dot.identifier()) {
            // Cant be a hex literal with a floating point at the same time in
            // the future we might have primitive types be classes ruby style so
            // someday this could be a feature But for now give an error on this
            if(hex)
              syntax_error("Found a . in a hex literal");

            is_float = true;
			ss << m_filebuffer.forward();
        }else{ // Quit if digit ends
            break;
		}
    }

  if(hex) {
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
{}

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
  std::stringstream buffer;
  while(std::isalnum(m_filebuffer.character()) && !m_filebuffer.eol())
    buffer << m_filebuffer.forward();

  // Verify if it is a keyword or not
  if(const auto token_type{is_keyword(buffer.str())};
     token_type != TokenType::UNKNOWN)
    {
      add_token(Token{token_type});
      std::cout << "Keyword: " << buffer.str() << std::endl;
  } else
    {
      add_token(Token{TokenType::IDENTIFIER, buffer.str()});
      std::cout << "Identifier: " << buffer.str() << std::endl;
    }
}

auto operator_logical() -> void
{}

auto operator_mutable() -> void
{}

auto operator_() -> void
{}

Tokenizer::Tokenizer(FileBuffer &t_filebuffer): m_filebuffer{t_filebuffer}
{
  m_tokenstream.reserve(256);
}

auto Tokenizer::tokenize() -> TokenStream
{
  using namespace reserved::symbols;

  for(; !m_filebuffer.eof(); m_filebuffer.next())
    for(; !m_filebuffer.eol(); m_filebuffer.forward())
      {
        const char character{m_filebuffer.character()};

        if(std::isalpha(character))
          identifier();
        else if(std::isdigit(character))
          literal_numeric();
        else if(character == g_double_quote.identifier())
          {
            // }else if() {
            // }else if() {
            // }else if() {
        }
      }

  return m_tokenstream;
}

Tokenizer::~Tokenizer()
{}
