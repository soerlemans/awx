#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>
#include <variant>

#include "tokentype.hpp"

template<typename T>
class Token {
private:
  using TokenValue = std::variant<int, double, std::string>;

  TokenType m_tokentype;
  TokenValue m_value;

public:
  explicit Token(T t_tokentype);
  explicit Token(T t_tokentype, int t_value);
  explicit Token(T t_tokentype, std::string t_value);

  auto type() const -> TokenType;

  template<typename T>
  auto value() const -> T
  {
	return std::get<T>(m_value);
  }

  template<typename T, typename Type=TokenType, typename Value=TokenValue>
  auto get() const -> std::tuple<TokenType, TokenValue>
  {
	return {m_tokentype, std::get<T>(m_value)};
  }

  virtual ~Token();
};

#endif // TOKEN_H
