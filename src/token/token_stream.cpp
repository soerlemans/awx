#include "token_stream.hpp"


// Reserve some space for the token steam for performance reasons in the future
// we might want to estimate the amount of tokens by looking at the amount of
// lines
TokenStream::TokenStream(const std::size_t t_reserve)
  : std::vector<Token>{}, m_index{0}
{
  this->reserve(t_reserve);
}

auto TokenStream::next(const int inc) -> Token&
{
  Token& result{(*this)[m_index]};

  m_index += inc;

  return result;
}

auto TokenStream::prev(const int dec) -> Token&
{
  Token& result{(*this)[m_index]};

  m_index += dec;

  return result;
}

auto TokenStream::token() -> Token&
{
  return (*this)[m_index];
}

auto TokenStream::eos() const -> bool
{
  return m_index >= size();
}


TokenStream::~TokenStream()
{
}