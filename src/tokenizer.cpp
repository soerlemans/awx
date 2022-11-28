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
  for(; !m_filebuffer.eof(); m_filebuffer++)
    for(std::size_t index{0}; index < m_filebuffer.line().size(); index++)
      {
        const std::string line{m_filebuffer.line()};
        const char character{line[index]};

        if(std::isalpha(character))
          {
            identifier();
        } else if(std::isdigit(character))
          {
            literal_numeric();
        }
      }

  return m_tokenstream;
}

Tokenizer::~Tokenizer()
{}
