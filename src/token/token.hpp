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
#include "../file_position.hpp"
#include "../stream.hpp"

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
  FilePosition m_file_pos;

  public:
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_type, const FilePosition& t_file_pos);
  explicit Token(TokenType t_type, TokenValue t_value,
                 const FilePosition& t_file_pos);

  auto type() const -> TokenType;

  auto value() const -> TokenValue;

  template<typename T>
  auto value() const -> T
  {
    return std::get<T>(m_value);
  }

  auto file_position() const -> const FilePosition&;

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  // Destructors:
  virtual ~Token() = default;
};
} // namespace token

#endif // AWX_TOKEN_TOKEN_HPP
