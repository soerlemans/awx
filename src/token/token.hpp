#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>
#include <type_traits>
#include <variant>

#include "token_type.hpp"

// Concepts:
template<typename T>
concept TokenValueConcept = std::same_as<T, int> || std::same_as<T, double>
                            || std::same_as<T, std::string>;

// Classes:
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
    requires TokenValueConcept<T>
  auto value() const -> T
  {
    return std::get<T>(m_value);
  }

  template<typename T, typename Type = TokenType,
           typename TokenValueType = TokenValue>
    requires TokenValueConcept<T>
  auto get() const -> std::tuple<TokenType, TokenValueType>
  {
    return {m_tokentype, std::get<T>(m_value)};
  }

  // The check() function should only be used for checking or verifying the
  // Value of the tokens value
  template<typename T>
    requires TokenValueConcept<T>
  auto check() const -> const T*
  {
    return std::get_if<T>(&m_value);
  }

  auto print() -> void;

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  virtual ~Token();
};

#endif // TOKEN_H
