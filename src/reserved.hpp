#ifndef RESERVED_H
#define RESERVED_H

#include <array>
#include <string_view>
#include <type_traits>

#include "tokentype.hpp"


// Macros:
// Do not use these macros outside of this file!
// TODO: Find a way to use templates to convert const char* to a std::string_view
// Macro used of defining/initializing a reserved keyword or symbol
#define DEFINE_RESERVED(name, id, token) \
  constexpr ReservedWrapper name         \
  {                                      \
    id, TokenType::token                 \
  }

// Concepts:
// The Identifier is either one character or
template<typename T>
concept ReservedIdentifier =
  std::same_as<T, std::string_view> || std::same_as<T, char>;

// AWX reserved keywords and symbols
namespace reserved {

  // Aliases:
  // Shorthand for string_view do not use outside of this namespace
  using r_vw = std::string_view;

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
  constexpr ReservedWrapper g_function2{std::string_view{"test"}, TokenType::FUNCTION_KEYWORD};
  DEFINE_RESERVED(g_function, r_vw{"function"}, FUNCTION_KEYWORD);
  DEFINE_RESERVED(g_if,       r_vw{"if"},       IF_KEYWORD);
  DEFINE_RESERVED(g_else,     r_vw{"else"},     ELSE_KEYWORD);
  DEFINE_RESERVED(g_do,       r_vw{"do"},       DO_KEYWORD);
  DEFINE_RESERVED(g_while,    r_vw{"while"},    WHILE_KEYWORD);
  DEFINE_RESERVED(g_for,      r_vw{"for"},      FOR_KEYWORD);
  DEFINE_RESERVED(g_in,       r_vw{"in"},       IN_KEYWORD);

  constexpr u8 keywords_size{7};
  constexpr std::array<ReservedWrapper<std::string_view>, keywords_size> g_keywords{
	g_function, g_if, g_else, g_do, g_while, g_for, g_in
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
  DEFINE_RESERVED(g_increment, r_vw{"++"}, INCREMENT);
  DEFINE_RESERVED(g_decrement, r_vw{"--"}, DECREMENT);

  // TODO: Rename or structure these better in the future?
  DEFINE_RESERVED(g_exponent_assignment,       r_vw{"^="}, EXPONENT_ASSIGNMENT);
  DEFINE_RESERVED(g_plus_assignment,           r_vw{"+="}, PLUS_ASSIGNMENT);
  DEFINE_RESERVED(g_minus_assignment,          r_vw{"-="}, MINUS_ASSIGNMENT);
  DEFINE_RESERVED(g_multiplication_assignment, r_vw{"*="}, MULTIPLICATION_ASSIGNMENT);
  DEFINE_RESERVED(g_division_assignment,       r_vw{"/="}, DIVISION_ASSIGNMENT);
  DEFINE_RESERVED(g_modulo_assignment,         r_vw{"%="}, MODULO_ASSIGNMENT);

  // Regex operators:
  DEFINE_RESERVED(g_ere_match,     '~',  ERE_MATCH);
  DEFINE_RESERVED(g_not_ere_match, r_vw{"!~"}, NOT_ERE_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_not,                  '!',  NOT);
  DEFINE_RESERVED(g_less_than,            '<',  LESS_THAN);
  DEFINE_RESERVED(g_less_than_equal, r_vw{"<="}, LESS_THAN_EQUAL);

  DEFINE_RESERVED(g_greater_than,            '>',  GREATER_THAN);
  DEFINE_RESERVED(g_greater_than_equal, r_vw{">="}, GREATER_THAN_EQUAL);

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
