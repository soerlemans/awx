#ifndef TOKEN_TYPE_WRAPPER_H
#define TOKEN_TYPE_WRAPPER_H


// Concepts:
// The Identifier is either one character or a string_view
template<typename T>
concept TokenTypeWrapperIdentifierConcept =
  std::same_as<T, std::string_view> || std::same_as<T, char>;

// AWX reserved keywords and symbols
namespace reserved {
// Helper class for the Reserved global variable definitions
// Is intended for attaching some more important data to a certain TokenType
template<typename T = std::string_view>
requires TokenTypeWrapperIdentifierConcept<T>
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

  constexpr auto identifier() const -> T
  {
    return m_identifier;
  }

  constexpr auto tokentype() const -> TokenType
  {
    return m_tokentype;
  }

  constexpr auto get() const -> std::tuple<T, TokenType>
  {
    return {m_identifier, m_tokentype};
  }

  // Warning: The class can be explicitly converted
  explicit constexpr operator TokenType() const
  {
    return m_tokentype;
  }

  ~TokenTypeWrapper() = default;
};

#endif // TOKEN_TYPE_WRAPPER_H
