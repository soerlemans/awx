#include <utility>

#include "tokenizer.hpp"

Tokenizer::Tokenizer(FileBuffer &&t_filebuffer)
  :m_filebuffer{t_filebuffer}
{

}

Tokenizer::~Tokenizer()
{}
