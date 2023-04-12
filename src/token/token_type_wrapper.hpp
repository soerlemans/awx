#ifndef TOKEN_TYPE_WRAPPER_HPP
#define TOKEN_TYPE_WRAPPER_HPP


#include <type_traits>
namespace token::reserved {
// Concepts:
// The Identifier is either one character or a string_view
template<typename T>
concept StringLike =
  std::is_convertible_v<T, std::string_view> || std::same_as<T, char>;

// AWX reserved keywords and symbols
// Helper class for the Reserved global variable definitions
// Is intended for attaching some more important data to a certain TokenType
template<typename T = std::string_view>
requires StringLike<T>
class TokenTypeWrapper {
  private:
  const T m_identifier;
  const TokenType m_tokentype;

  public:
  // TODO: Use std::is_convertible<T, std::string_view> to not need to cast to
  // std::string_view explicitly
  constexpr TokenTypeWrapper(T t_identifier, TokenType t_tokentype)
    : m_identifier{t_identifier}, m_tokentype{t_tokentype}
  {}

  constexpr TokenTypeWrapper(const char* t_identifier, TokenType t_tokentype)
    : m_identifier{t_identifier}, m_tokentype{t_tokentype}
  {}

  [[nodiscard]] constexpr auto identifier() const -> T
  {
    return m_identifier;
  }

  [[nodiscard]] constexpr auto tokentype() const -> TokenType
  {
    return m_tokentype;
  }

  [[nodiscard]] constexpr auto get() const -> std::tuple<T, TokenType>
  {
    return {m_identifier, m_tokentype};
  }

  // Warning: The class can be explicitly converted
  [[nodiscard]] explicit constexpr operator TokenType() const
  {
    return m_tokentype;
  }

  ~TokenTypeWrapper() = default;
};
} // namespace token::reserved

#endif // TOKEN_TYPE_WRAPPER_HPP
