#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>

#include "../file_position.hpp"

#include "token_type.hpp"


// Concepts:
template<typename T>
concept TokenValueConcept =
  std::same_as<T, int> || std::same_as<T, double> || std::same_as<T,
                                                                  std::string>;

// Classes:
class Token {
  private:
  using TokenValue = std::variant<int, double, std::string>;

  TokenType m_type;
  TokenValue m_value;

  // Records position in a file, useful for indicating errors
  FilePosition m_file_pos;

  public:
  // Constructors:
  Token() = default;
  Token(const Token& t_token) = default;

  explicit Token(TokenType t_type, const FilePosition& t_file_pos);

  template<typename T>
  requires TokenValueConcept<T>
  explicit Token(TokenType t_type, T t_value, const FilePosition& t_file_pos)
    : m_type{t_type}, m_value{t_value}, m_file_pos{t_file_pos}
  {}

  // Methods:
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
    return {m_type, std::get<T>(m_value)};
  }

  // The check() function should only be used for checking or verifying the
  // Value of the tokens value
  template<typename T>
  requires TokenValueConcept<T>
  auto check() const -> const T*
  {
    return std::get_if<T>(&m_value);
  }

  auto file_position() const -> const FilePosition&;

  template<typename T>
  auto print_if(std::string_view t_str_vw) const -> bool
  {
    bool is_type{false};

    if(const auto verify{check<T>()}; verify) {
      std::cout << t_str_vw << ": " << *verify << '\n';

      is_type = true;
    }

    return is_type;
  }

  auto print() const -> void;

  // Operators
  auto operator=(const Token& t_token) -> Token& = default;
  auto operator=(Token&& t_token) -> Token& = default;

  // Destructors:
  virtual ~Token() = default;
};

#endif // TOKEN_HPP
