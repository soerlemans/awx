#ifndef AWX_TOKEN_TOKEN_HPP
#define AWX_TOKEN_TOKEN_HPP

// STL Includes:
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

// Includes:
#include "../container/text_position.hpp"
#include "../container/stream.hpp"

// Local Includes:
#include "token_type.hpp"


namespace token {
// Forward Declarations:
class Token;

// Aliases:
using TokenStream = Stream<std::vector<Token>>;

// Classes:
class Token {
  private:
  using TokenValue = std::variant<int, double, std::string>;

  TokenType m_type;
  TokenValue m_value;

  // Records position in a file, useful for indicating errors
  container::TextPosition m_pos;

  public:
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_type, const container::TextPosition& t_pos);
  explicit Token(TokenType t_type, TokenValue t_value,
                 const container::TextPosition& t_pos);

  auto type() const -> TokenType;

  auto value() const -> TokenValue;

  template<typename T>
  auto value() const -> T
  {
    return std::get<T>(m_value);
  }

  auto position() const -> const container::TextPosition&;

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  // Destructors:
  virtual ~Token() = default;
};
} // namespace token

#endif // AWX_TOKEN_TOKEN_HPP
