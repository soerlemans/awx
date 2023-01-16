#ifndef RESERVED_H
#define RESERVED_H

#include <array>
#include <string_view>
#include <type_traits>

#include "token_type.hpp"


// Macros:
// Do not use these macros outside of this file!
// TODO: Find a way to use templates to convert const char* to a
// std::string_view Macro used of defining/initializing a reserved keyword or
// symbol
#define DEFINE_RESERVED(name, id, token) \
  constexpr TokenTypeWrapper name        \
  {                                      \
    id, TokenType::token                 \
  }

// Concepts:
// The Identifier is either one character or
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

// clang-format off
// Language reserved keywords
namespace keywords {
  DEFINE_RESERVED(g_function, "function", FUNCTION);
  DEFINE_RESERVED(g_return,   "return",   RETURN);

  DEFINE_RESERVED(g_if,   "if",   IF);
  DEFINE_RESERVED(g_else, "else", ELSE);

  DEFINE_RESERVED(g_do,    "do",    DO);
  DEFINE_RESERVED(g_while, "while", WHILE);
  DEFINE_RESERVED(g_for,   "for",   FOR);
  DEFINE_RESERVED(g_in,    "in",    IN);

  DEFINE_RESERVED(g_break,    "break",    BREAK);
  DEFINE_RESERVED(g_continue, "continue", CONTINUE);

  DEFINE_RESERVED(g_next, "next", NEXT);
  DEFINE_RESERVED(g_exit, "exit", EXIT);

  DEFINE_RESERVED(g_delete, "delete", DELETE);

  DEFINE_RESERVED(g_print,   "print",   PRINT);
  DEFINE_RESERVED(g_printf,  "printf",  PRINTF);
  DEFINE_RESERVED(g_getline, "getline", GETLINE);

  DEFINE_RESERVED(g_begin, "BEGIN", BEGIN);
  DEFINE_RESERVED(g_end,   "END",   END);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  // TODO: Make these be generated automagically
  // TODO: Make this a constexpr vector? those have constexpr initializer_list constructor
  constexpr std::array<TokenTypeWrapper<std::string_view>, 18> g_keywords{
	g_function, g_return,
	g_if, g_else,
	g_do, g_while, g_for, g_in,
	g_break, g_continue,
	g_next, g_exit,
	g_delete,
	g_print, g_printf, g_getline,
	g_begin, g_end
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
  DEFINE_RESERVED(g_caret,        '^', CARET);
  DEFINE_RESERVED(g_plus,         '+', PLUS);
  DEFINE_RESERVED(g_minus,        '-', MINUS);
  DEFINE_RESERVED(g_asterisk,     '*', ASTERISK);
  DEFINE_RESERVED(g_slash,        '/', SLASH);
  DEFINE_RESERVED(g_percent_sign, '%', PERCENT_SIGN);

  // Assignment variants of Arithmetic operators:
  DEFINE_RESERVED(g_increment, "++", INCREMENT);
  DEFINE_RESERVED(g_decrement, "--", DECREMENT);

  // TODO: Rename or structure these better in the future?
  DEFINE_RESERVED(g_power_assignment,    "^=", POWER_ASSIGNMENT);
  DEFINE_RESERVED(g_add_assignment,      "+=", ADD_ASSIGNMENT);
  DEFINE_RESERVED(g_subtract_assignment, "-=", SUBTRACT_ASSIGNMENT);
  DEFINE_RESERVED(g_multiply_assignment, "*=", MULTIPLY_ASSIGNMENT);
  DEFINE_RESERVED(g_divide_assignment,   "/=", DIVIDE_ASSIGNMENT);
  DEFINE_RESERVED(g_modulo_assignment,   "%=", MODULO_ASSIGNMENT);

  // Regex operators:
  DEFINE_RESERVED(g_ere_match,     '~',  ERE_MATCH);
  DEFINE_RESERVED(g_not_ere_match, "!~", NOT_ERE_MATCH);

  // Logic operators:
  DEFINE_RESERVED(g_or,  "||", OR);
  DEFINE_RESERVED(g_and, "&&", AND);

  DEFINE_RESERVED(g_not,             '!',   NOT);
  DEFINE_RESERVED(g_less_than,       '<',   LESS_THAN);
  DEFINE_RESERVED(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_RESERVED(g_equal,     "==", EQUAL);
  DEFINE_RESERVED(g_not_equal, "!=", NOT_EQUAL);

  DEFINE_RESERVED(g_greater_than,       '>',   GREATER_THAN);
  DEFINE_RESERVED(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Control flow symbols:
  DEFINE_RESERVED(g_comma,        ',', COMMA);
  DEFINE_RESERVED(g_dot,          '.', DOT);
  DEFINE_RESERVED(g_questionmark, '?', QUESTIONMARK);
  DEFINE_RESERVED(g_colon,        ':', COLON);
  DEFINE_RESERVED(g_semicolon,    ';', SEMICOLON);

  // Output redirection:
  DEFINE_RESERVED(g_trunc,  '>',  TRUNC);
  DEFINE_RESERVED(g_append, ">>", APPEND);
  DEFINE_RESERVED(g_pipe,   '|',  PIPE);

  // Miscellaneous operators:
  DEFINE_RESERVED(g_dollar_sign,  '$',  DOLLAR_SIGN);
  DEFINE_RESERVED(g_newline,  '\n', NEWLINE);

  // TODO: Make these be generated automagically
  // TODO: Place these  somewhere else they are ugly
  constexpr std::array<TokenTypeWrapper<char>, 26>
  g_single_symbols{
	g_paren_open,
	g_paren_close,
	g_accolade_open,
	g_accolade_close,
	g_brace_open,
	g_brace_close,

	g_assignment,

	g_caret,
	g_plus,
	g_minus,
	g_asterisk,
	g_slash,
	g_percent_sign,

	g_ere_match,

	g_not,
	g_less_than,
	g_greater_than,

	g_comma,
	g_dot,
	g_questionmark,
	g_colon,
	g_semicolon,

	g_trunc,
	g_pipe,

	g_dollar_sign,
	g_newline
  };

  constexpr std::array<TokenTypeWrapper<std::string_view>, 16>
  g_multi_symbols{
	g_increment,
	g_decrement,

	g_power_assignment,
	g_add_assignment,
	g_subtract_assignment,
	g_multiply_assignment,
	g_divide_assignment,
	g_modulo_assignment,

	g_not_ere_match,

	g_or,
	g_and,

	g_less_than_equal,

	g_equal,
	g_not_equal,

	g_greater_than_equal,

	g_append
  };

// Contains symbols that have a special meaning but are not tied to a Token
namespace none {
  // String literal symbols
  DEFINE_RESERVED(g_double_quote, '"', NONE);
  DEFINE_RESERVED(g_backslash, '\\',  NONE);
}; // namespace unknown
}; // namespace symbols

// clang-format on
}; // namespace reserved

#endif // RESERVED_H
