#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <typle>
#include <variant>

#include "tokentype.hpp"


class Token {
private:
  using enum TokenType;

  TokenType m_tokentype{UNKNOWN};
  std::variant<int, std::string> m_value;

public:
  explicit Token(t_tokentype, int t_value)
	:m_tokentype{t_tokentype}, m_value{t_value}
  {};

  explicit Token(t_tokentype, std::string t_value)
	:m_tokentype{t_tokentype}, m_value{t_value}
  {};

  auto get_type() -> TokenType
  {
	return m_tokentype;
  }

  template<typename T>
  auto get_value() -> T
  {
	return std::get<T>(m_value);
  }

  // template<typename T>
  // auto get() -> std::tuple<TokenType, std::var

  virtual ~Token();
};

#endif // TOKEN_H
