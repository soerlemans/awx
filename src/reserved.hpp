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
  // TODO: Use std::is_convertible<T, std::string_view> to not need to cast to
  // std::string_view explicitly
  constexpr ReservedWrapper(T t_indentifier, TokenType t_tokentype)
    : m_identifier{t_indentifier}, m_tokentype{t_tokentype}
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

  ~ReservedWrapper() = default;
};

// clang-format off
// Language reserved keywords
namespace keywords {
  DEFINE_RESERVED(g_function, r_vw{"function"}, FUNCTION_KEYWORD);
  DEFINE_RESERVED(g_if,       r_vw{"if"},       IF_KEYWORD);
  DEFINE_RESERVED(g_else,     r_vw{"else"},     ELSE_KEYWORD);
  DEFINE_RESERVED(g_do,       r_vw{"do"},       DO_KEYWORD);
  DEFINE_RESERVED(g_while,    r_vw{"while"},    WHILE_KEYWORD);
  DEFINE_RESERVED(g_for,      r_vw{"for"},      FOR_KEYWORD);
  DEFINE_RESERVED(g_in,       r_vw{"in"},       IN_KEYWORD);

  // TODO: Make these be generated automagically
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
  DEFINE_RESERVED(g_ere_match,          '~',   ERE_MATCH);
  DEFINE_RESERVED(g_not_ere_match, r_vw{"!~"}, NOT_ERE_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_not,                  '!',   NOT);
  DEFINE_RESERVED(g_less_than,            '<',   LESS_THAN);
  DEFINE_RESERVED(g_less_than_equal, r_vw{"<="}, LESS_THAN_EQUAL);

  DEFINE_RESERVED(g_greater_than,            '>',   GREATER_THAN);
  DEFINE_RESERVED(g_greater_than_equal, r_vw{">="}, GREATER_THAN_EQUAL);

  // Control flow symbols:
  DEFINE_RESERVED(g_comma,        ',', COMMA);
  DEFINE_RESERVED(g_dot,          '.', DOT);
  DEFINE_RESERVED(g_questionmark, '?', QUESTIONMARK);
  DEFINE_RESERVED(g_colon,        ':', COLON);
  DEFINE_RESERVED(g_semicolon,    ';', SEMICOLON);

  // Miscellaneous operators:
  DEFINE_RESERVED(g_dollar_sign, '$',  DOLLAR_SIGN);
  DEFINE_RESERVED(g_end_of_line, '\n', END_OF_LINE);

  // TODO: Make these be generated automagically
  // TODO: Place these  somewhere else they are ugly
  constexpr u8 single_symbol_size{24};
  constexpr std::array<ReservedWrapper<char>, single_symbol_size>
  g_single_symbols{
	g_paren_open,
	g_paren_close,
	g_accolade_open,
	g_accolade_close,
	g_brace_open,
	g_brace_close,

	g_assignment,

	g_exponent,
	g_plus,
	g_minus,
	g_multiplier,
	g_divider,
	g_modulus,

	g_ere_match,

	g_not,
	g_less_than,
	g_greater_than,

	g_comma,
	g_dot,
	g_questionmark,
	g_colon,
	g_semicolon,

	g_dollar_sign,
	g_end_of_line
  };

  constexpr u8 multi_symbol_size{11};
  constexpr std::array<ReservedWrapper<std::string_view>, multi_symbol_size>
  g_multi_symbols{
	g_increment,
	g_decrement,

	g_exponent_assignment,
	g_plus_assignment,
	g_minus_assignment,
	g_multiplication_assignment,
	g_division_assignment,
	g_modulo_assignment,

	g_not_ere_match,
	g_less_than_equal,
	g_greater_than_equal
  };

// Contains symbols that have a special meaning but are not tiedto a Token
namespace none {
  // String literal symbols
  // TODO: Create an extra tokentype called NONE, or EMPTY
  DEFINE_RESERVED(g_double_quote, '"', NONE);
  DEFINE_RESERVED(g_backslash, '\\',  NONE);
}; // namespace unknown
}; // namespace symbols

// clang-format on
}; // namespace reserved

#endif // RESERVED_H
