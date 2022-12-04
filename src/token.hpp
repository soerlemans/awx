#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>
#include <variant>

#include "tokentype.hpp"

class Token {
private:
  using TokenValue = std::variant<int, double, std::string>;

  TokenType m_tokentype;
  TokenValue m_value;

public:
  // TODO: Replace these constructors with a template with a restrictive concept
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_tokentype);
  explicit Token(TokenType t_tokentype, int t_value);
  explicit Token(TokenType t_tokentype, double t_value);
  explicit Token(TokenType t_tokentype, std::string t_value);

  auto type() const -> TokenType;

  template<typename T>
  auto value() const -> T
  {
	return std::get<T>(m_value);
  }

  template<typename T, typename Type=TokenType, typename TokenValueType=TokenValue>
  auto get() const -> std::tuple<TokenType, TokenValueType>
  {
	return {m_tokentype, std::get<T>(m_value)};
  }

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  virtual ~Token();
};

#endif // TOKEN_H
