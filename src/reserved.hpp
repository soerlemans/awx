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
concept ReservedIdentifier = std::is_convertible_v<T, std::string_view>
                             || std::same_as<std::remove_cv<T>, char>;

// AWX reserved keywords and symbols
namespace reserved {
// Helper class for the Reserved global variable definitions
template<typename T>
  requires ReservedIdentifier<T>
class ReservedWrapper {
  private:
  const T m_identifier;
  const TokenType m_tokentype;

  public:
  constexpr ReservedWrapper(T t_indentifier, TokenType t_tokentype = TokenType::UNKNOWN)
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
  DEFINE_RESERVED(g_function, "function", TokenType::FUNCTION_KEYWORD);
  DEFINE_RESERVED(g_if, "if", TokenType::IF_KEYWORD);
  DEFINE_RESERVED(g_else, "else", TokenType::ELSE_KEYWORD);
  DEFINE_RESERVED(g_do, "do", TokenType::DO_KEYWORD);
  DEFINE_RESERVED(g_while, "while", TokenType::WHILE_KEYWORD);
  DEFINE_RESERVED(g_for, "for", TokenType::FOR_KEYWORD);
  DEFINE_RESERVED(g_in, "in", TokenType::IN_KEYWORD);

  constexpr u8 keywords_size{7};
  std::array<ReservedWrapper, keywords_size> m_keywords{}
}; // namespace keywords

// Language reserved symbols
namespace symbols {
  // Braces
  DEFINE_RESERVED(g_paren_open,     '(', TokenType::PAREN_OPEN);
  DEFINE_RESERVED(g_paren_close,    ')', TokenType::PAREN_CLOSE);
  DEFINE_RESERVED(g_accolade_open,  '{', TokenType::ACCOLADE_OPEN);
  DEFINE_RESERVED(g_accolade_close, '}', TokenType::ACCOLADE_CLOSE);
  DEFINE_RESERVED(g_brace_open,     '[', TokenType::BRACE_OPEN);
  DEFINE_RESERVED(g_brace_close,    ']', TokenType::BRACE_CLOSE);

  // String literal symbols
  // TODO: Create an extra tokentype called NONE, or EMPTY
  DEFINE_RESERVED(g_double_quote, '"');

  // Assignment
  DEFINE_RESERVED(g_assignment, '=',  TokenType::ASSIGNMENT);

  // Arithmetic operators:
  DEFINE_RESERVED(g_exponent,   '^', TokenType::EXPONENT);
  DEFINE_RESERVED(g_plus,       '+', TokenType::PLUS);
  DEFINE_RESERVED(g_minus,      '-', TokenType::MINUS);
  DEFINE_RESERVED(g_multiplier, '*', TokenType::MULTIPLIER);
  DEFINE_RESERVED(g_divider,    '/', TokenType::DIVIDER);
  DEFINE_RESERVED(g_modulus,    '%', TokenType::MODULUS);

  // Assignment variants of Arithmetic operators:
  DEFINE_RESERVED(g_increment, "++", TokenType::INCREMENT);
  DEFINE_RESERVED(g_decrement, "--", TokenType::DECREMENT);

  // TODO: Rename or structure these better in the future?
  DEFINE_RESERVED(g_exponent_assignment,       "^=", TokenType::EXPONENT_ASSIGNMENT);
  DEFINE_RESERVED(g_plus_assignment,           "+=", TokenType::PLUS_ASSIGNMENT);
  DEFINE_RESERVED(g_minus_assignment,          "-=", TokenType::MINUS_ASSIGNMENT);
  DEFINE_RESERVED(g_multiplication_assignment, "*=", TokenType::MULTIPLICATION_ASSIGNMENT);
  DEFINE_RESERVED(g_division_assignment,       "/=", TokenType::DIVISION_ASSIGNMENT);
  DEFINE_RESERVED(g_modulo_assignment,         "%=", TokenType::MODULO_ASSIGNMENT);

  // Regex operators:
  DEFINE_RESERVED(g_ere_match, '~', TokenType::ERE_MATCH);
  DEFINE_RESERVED(g_not_ere_match, "!~", TokenType::NOT_ERE_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_not, '!');
  DEFINE_RESERVED(g_less_than, '<');
  DEFINE_RESERVED(g_less_than_equal, '<');

  DEFINE_RESERVED(g_greater_than, '>');
  DEFINE_RESERVED(g_greater_than_equal, '>');

  // Control flow symbols
  DEFINE_RESERVED(g_comma, ',');
  DEFINE_RESERVED(g_questionmark, '?');
  DEFINE_RESERVED(g_colon, ':');
  DEFINE_RESERVED(g_semicolon, ';');

  // Miscellaneous operators:
  DEFINE_RESRVED(g_dollar_sign, '$');
  DEFINE_RESRVED(g_end_of_line, '\n');

// clang-format on
}; // namespace symbols
}; // namespace reserved

#endif // RESERVED_H
