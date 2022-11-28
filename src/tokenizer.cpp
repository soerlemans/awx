#include <cctype>
#include <iostream>
#include <sstream>

#include "tokenizer.hpp"


auto Tokenizer::single_character() -> void
{}
auto Tokenizer::literal_numeric() -> void
{}
auto Tokenizer::literal_string() -> void
{}

auto Tokenizer::keyword() -> void
{}

auto Tokenizer::identifier() -> void
{
  std::stringstream buffer;
}

auto operator_logical() -> void
{}
auto operator_mutable() -> void
{}
auto operator_() -> void
{}

Tokenizer::Tokenizer(FileBuffer &t_filebuffer)
  : m_filebuffer{t_filebuffer}
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

        if(std::isalpha(character)) {
		  identifier();
        }else if(std::isdigit(character)) {
		  literal_numeric();
        }else if(character == g_double_quote) {
		  std::cout << "I found a string character\n";
        // }else if() {
        // }else if() {
        // }else if() {
		  
		}
      }

  return m_tokenstream;
}

Tokenizer::~Tokenizer()
{}
