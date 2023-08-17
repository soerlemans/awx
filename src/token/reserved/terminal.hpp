#ifndef AWX_TOKEN_RESERVED_TERMINAL_HPP
#define AWX_TOKEN_RESERVED_TERMINAL_HPP

// STL Includes:
#include <type_traits>

// Includes:
#include "../token_type.hpp"

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
struct Terminal {
  T m_identifier;
  TokenType m_type;

  constexpr Terminal(T t_identifier, TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  constexpr Terminal(const char* t_identifier, TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  virtual ~Terminal() = default;
};
} // namespace token::reserved

#endif // AWX_TOKEN_RESERVED_TERMINAL_HPP
