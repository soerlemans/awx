#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>
#include <variant>

#include "tokentype.hpp"

class Token {
private:
  using enum TokenType;
  using TokenValue = std::variant<int, std::string>;

  TokenType m_tokentype{UNKNOWN};
  TokenValue m_value;

public:
  explicit Token(TokenType t_tokentype, int t_value);
  explicit Token(TokenType t_tokentype, std::string t_value);

  auto type() const -> TokenType;

  template<typename T>
  auto value() const -> T
  {
	return std::get<T>(m_value);
  }

  template<typename T, typename Type=TokenType, typename Value=TokenValue>
  auto get() const -> std::tuple<TokenType, TokenValue>
  {
	return std::tuple<Type, Value>{m_tokentype, std::get<T>(m_value)};
  }

  virtual ~Token();
};

#endif // TOKEN_H
