#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>
#include <variant>

#include "token_type.hpp"

class Token {
private:
  using TokenValue = std::variant<int, double, std::string>;

  TokenType m_token_type;
  TokenValue m_value;

public:
  // TODO: Replace these constructors with a template with a restrictive concept
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_token_type);
  explicit Token(TokenType t_token_type, int t_value);
  explicit Token(TokenType t_token_type, double t_value);
  explicit Token(TokenType t_token_type, std::string t_value);

  auto type() const -> TokenType;

  template<typename T>
  auto value() const -> T
  {
	return std::get<T>(m_value);
  }

  template<typename T, typename Type=TokenType, typename TokenValueType=TokenValue>
  auto get() const -> std::tuple<TokenType, TokenValueType>
  {
	return {m_token_type, std::get<T>(m_value)};
  }

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  virtual ~Token();
};

#endif // TOKEN_H
