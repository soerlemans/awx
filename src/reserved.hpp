#ifndef RESERVED_H
#define RESERVED_H

#include <array>
#include <string_view>
#include <type_traits>

#include "tokentype.hpp"


// Macros:
// Do not use this macro outside of this file
#define DEFINE_RESERVED(name, str, token) \
  constexpr ReservedWrapper name          \
  {                                       \
    str, TokenType::token                 \
  }

// Concepts:
// The Identifier is either one character or
template<typename T>
concept ReservedIdentifier =
  std::is_convertible_v<T, std::string_view> || std::same_as<T, char>;

// AWX reserved keywords and symbols
namespace reserved {
// Helper class for the Reserved global variable definitions
template<typename T = char>
  requires ReservedIdentifier<T>
class ReservedWrapper {
  private:
  const T m_identifier;
  const TokenType m_tokentype;

  public:
  constexpr ReservedWrapper(T t_indentifier, TokenType t_tokentype)
    : m_identifier{t_indentifier}, m_tokentype{t_tokentype}
  {}

  auto identifier() const -> T
  {
    return m_identifier;
  }

  auto tokentype() const -> TokenType
  {
    return m_tokentype;
  }

  auto get() const -> std::tuple<T, TokenType>
  {
    return {m_identifier, m_tokentype};
  }

  ~ReservedWrapper() = default;
};

// clang-format off
// Language reserved keywords
namespace keywords {
  DEFINE_RESERVED(g_function, "function", FUNCTION_KEYWORD);
  DEFINE_RESERVED(g_if, "if", IF_KEYWORD);
  DEFINE_RESERVED(g_else, "else", ELSE_KEYWORD);
  DEFINE_RESERVED(g_do, "do", DO_KEYWORD);
  DEFINE_RESERVED(g_while, "while", WHILE_KEYWORD);
  DEFINE_RESERVED(g_for, "for", FOR_KEYWORD);
  DEFINE_RESERVED(g_in, "in", IN_KEYWORD);

  constexpr u8 keywords_size{7};
  std::array<ReservedWrapper<const char*>, keywords_size> m_keywords{
	g_function,
	g_if, g_else,
	g_do, g_while,
	g_for, g_in
  };
}; // namespace keywords

// Language reserved symbols
namespace symbols {
  // Braces
  DEFINE_RESERVED(g_paren_open,     '(', PAREN_OPEN);
  DEFINE_RESERVED(g_paren_close,    ')', PAREN_CLOSE);
  DEFINE_RESERVED(g_accolade_open,  '{', ACCOLADE_OPEN);
  DEFINE_RESERVED(g_accolade_close, '}', ACCOLADE_CLOSE);
  DEFINE_RESERVED(g_brace_open,     '[', BRACE_OPEN);
  DEFINE_RESERVED(g_brace_close,    ']', BRACE_CLOSE);

  // String literal symbols
  // TODO: Create an extra tokentype called NONE, or EMPTY
  DEFINE_RESERVED(g_double_quote, '"', UNKNOWN);

  // Assignment
  DEFINE_RESERVED(g_assignment, '=', ASSIGNMENT);

  // Arithmetic operators:
  DEFINE_RESERVED(g_exponent,   '^', EXPONENT);
  DEFINE_RESERVED(g_plus,       '+', PLUS);
  DEFINE_RESERVED(g_minus,      '-', MINUS);
  DEFINE_RESERVED(g_multiplier, '*', MULTIPLIER);
  DEFINE_RESERVED(g_divider,    '/', DIVIDER);
  DEFINE_RESERVED(g_modulus,    '%', MODULUS);

  // Assignment variants of Arithmetic operators:
  DEFINE_RESERVED(g_increment, "++", INCREMENT);
  DEFINE_RESERVED(g_decrement, "--", DECREMENT);

  // TODO: Rename or structure these better in the future?
  DEFINE_RESERVED(g_exponent_assignment,       "^=", EXPONENT_ASSIGNMENT);
  DEFINE_RESERVED(g_plus_assignment,           "+=", PLUS_ASSIGNMENT);
  DEFINE_RESERVED(g_minus_assignment,          "-=", MINUS_ASSIGNMENT);
  DEFINE_RESERVED(g_multiplication_assignment, "*=", MULTIPLICATION_ASSIGNMENT);
  DEFINE_RESERVED(g_division_assignment,       "/=", DIVISION_ASSIGNMENT);
  DEFINE_RESERVED(g_modulo_assignment,         "%=", MODULO_ASSIGNMENT);

  // Regex operators:
  DEFINE_RESERVED(g_ere_match,     '~',  ERE_MATCH);
  DEFINE_RESERVED(g_not_ere_match, "!~", NOT_ERE_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_not,             '!',  NOT);
  DEFINE_RESERVED(g_less_than,       '<',  LESS_THAN);
  DEFINE_RESERVED(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_RESERVED(g_greater_than,       '>',  GREATER_THAN);
  DEFINE_RESERVED(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Control flow symbols:
  DEFINE_RESERVED(g_comma,        ',', COMMA);
  DEFINE_RESERVED(g_questionmark, '?', QUESTIONMARK);
  DEFINE_RESERVED(g_colon,        ':', COLON);
  DEFINE_RESERVED(g_semicolon,    ';', SEMICOLON);

  // Miscellaneous operators:
  DEFINE_RESERVED(g_dollar_sign, '$',  DOLLAR_SIGN);
  DEFINE_RESERVED(g_end_of_line, '\n', END_OF_LINE);

// clang-format on
}; // namespace symbols
}; // namespace reserved

#endif // RESERVED_H
