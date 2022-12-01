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
  explicit Token(TokenType t_tokentype);
  explicit Token(TokenType t_tokentype, int t_value);
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

  virtual ~Token();
};

#endif // TOKEN_H
