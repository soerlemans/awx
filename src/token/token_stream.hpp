#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <vector>

#include "token.hpp"


// Default amount of space to reserve for tokens in a TokenStream
enum {
  TOKENSTREAM_RESERVE = 256
};

// Manages a TokenStream in a statefull way so it is aware
// If the use for a stream that knows its position is need for more objects
// Make this a general class that accepts a template argument
class TokenStream : public std::vector<Token> {
  private:
  std::size_t m_index{0};

  public:
  // Constructors:
  // TODO: Change 256 to not be a magic constant
  explicit TokenStream(std::size_t t_reserve = TOKENSTREAM_RESERVE);

  auto next(std::size_t inc = 1) -> Token&;
  auto prev(std::size_t dec = 1) -> Token&;

  auto token() -> Token&;

  auto eos() const -> bool;

  // Destructors:
  virtual ~TokenStream() = default;
};

#endif // TOKEN_STREAM_H
