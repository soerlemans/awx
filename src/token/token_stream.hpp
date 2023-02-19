#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <stack>
#include <vector>

#include "token.hpp"


// Default amount of space to reserve for tokens in a TokenStream
enum { TOKENSTREAM_RESERVE = 256 };

// Manages a TokenStream in a statefull way so it is aware
// If the use for a stream that knows its position is need for more objects
// Make this a general class that accepts a template argument
class TokenStream : public std::vector<Token> {
  private:
  std::size_t m_index{0};
  std::stack<std::size_t> m_stack;

  public:
  explicit TokenStream(std::size_t t_reserve = TOKENSTREAM_RESERVE);

  // Go to next or previous token
  auto next() -> Token&;
  auto prev() -> Token&;

  // Save and restore the current index (for lookahead purposes)
  auto save() -> void;
  auto restore() -> void;

  auto token() -> Token&;

  auto eos() const -> bool;

  virtual ~TokenStream() = default;
};

#endif // TOKEN_STREAM_H
