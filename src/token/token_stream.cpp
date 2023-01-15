#include "token_stream.hpp"


// Constructors:
// Reserve some space for the token steam for performance reasons in the future
// we might want to estimate the amount of tokens by looking at the amount of
// lines
TokenStream::TokenStream(const std::size_t t_reserve)
  : std::vector<Token>{}, m_index{0}
{
  this->reserve(t_reserve);
}

// Methods:
auto TokenStream::next(const std::size_t t_inc) -> Token&
{
  Token& result{(*this)[m_index]};

  m_index += t_inc;

  return result;
}

auto TokenStream::prev(const std::size_t t_dec) -> Token&
{
  Token& result{(*this)[m_index]};

  // Logically you can go past a stream but not in front of a stream
  if(m_index >= t_dec)
    m_index -= t_dec;
  else
    m_index = 0;

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

// Destructors:
TokenStream::~TokenStream()
{}
