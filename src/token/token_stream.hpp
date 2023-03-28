#ifndef TOKEN_STREAM_HPP
#define TOKEN_STREAM_HPP

// STL Includes:
#include <stack>
#include <vector>

#include "token.hpp"


// TODO: We reserve twice a size of 256 possible inherit from vector and have
// The default be 256 Default amount of space to reserve for tokens in a
// TokenStream
enum { DEFAULT_RESERVE = 256 };

// Manages a TokenStream in a statefull way so it is aware
// If the use for a stream that knows its position is need for more objects
// Make this a general class that accepts a template argument
class TokenStream : public std::vector<Token> {
  private:
  std::size_t m_index{0};
  std::stack<std::size_t> m_stack;

  public:
  explicit TokenStream(std::size_t t_reserve = DEFAULT_RESERVE);

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

#endif // TOKEN_STREAM_HPP
