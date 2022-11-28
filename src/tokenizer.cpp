#include <cctype>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "exception.hpp"
#include "tokenizer.hpp"


// Helper function to literal_numeric
auto Tokenizer::is_hex() -> bool
{
  // Octal literals are not specified in the POSIX AWK standard
  // So just discard leading zeros
  if(m_filebuffer.character() == '0')
    {
      m_filebuffer.forward();
      // TODO: Define reserved hex literal symbol
      // If the next character is a 'x' it must be a hex literal
      if(m_filebuffer.character() == 'x')
		{
		  m_filebuffer.forward();

		  return true;
		}
  }
  return false;
}

// Helper function for literal_numeric
auto Tokenizer::is_float() -> bool
{}

auto Tokenizer::literal_numeric() -> void
{
  std::stringstream ss;

  bool hex{is_hex()};
  bool dot{false};
  std::size_t dot_pos{0};

  // TODO: Make separate function for handling hex literals
  // TODO: Make separate function for handling floats
  if(!hex)
	ss << m_filebuffer.character();

  while(!m_filebuffer.eol())
    {
	  std::cout << std::boolalpha << "hex: " << hex << " dot: " << dot << " ss: " << ss.str() << " line: " << m_filebuffer.line() << '\n';
      const char character{m_filebuffer.character()};

      // Check for integer
      if(std::isdigit(character)) {
          ss << m_filebuffer.forward();

          // Check for floating point
          // TODO: Define dot reserved symbol
      }else if(!dot && character == '.') {
          // Cant be a hex literal with a floating point at the same time
          // This could be a feature if we add methods to literal types
          // But for now give an error on this
		// FIXME: The ^^^ does not properly align, columnno is possibly not properly adjusted
          if(hex)
            throw SyntaxError{"Found a . in a hex literal", m_filebuffer.lineno(),
                              m_filebuffer.line(), m_filebuffer.columnno()};

		  dot = true;
		  dot_pos = m_filebuffer.columnno();
      }else
		break;
    }

  std::cout << "number found! " << ss.str() << '\n';
}

auto Tokenizer::literal_string() -> void
{}

auto Tokenizer::keyword() -> void
{}

auto Tokenizer::identifier() -> void
{
  std::stringstream buffer;
  while(std::isalnum(m_filebuffer.character()) && !m_filebuffer.eol())
    buffer << m_filebuffer.forward();

  std::cout << "identifier found! " << buffer.str() << '\n';
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
        else if(character == g_double_quote)
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
