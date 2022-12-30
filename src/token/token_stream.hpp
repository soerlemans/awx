#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <vector>

#include "token.hpp"


// Manages a TokenStream in a statefull way so it is aware
// If the use for a stream that knows its position is need for more objects
// Make this a general class that accepts a template argument
class TokenStream : public std::vector<Token>
{
  private:
  std::size_t m_index;

  public:
  TokenStream(const std::size_t t_reserve = 256);

  auto next(const int inc = 1) -> Token&;
  auto prev(const int dec = 1) -> Token&;

  auto token() -> Token&;

  auto eos() const -> bool;

  virtual ~TokenStream();
};

#endif // TOKEN_STREAM_H
