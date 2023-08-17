#ifndef AWX_TOKEN_RESERVED_RESERVED_HPP
#define AWX_TOKEN_RESERVED_RESERVED_HPP

// STL Includes:
#include <array>
#include <string_view>
#include <type_traits>

// Local Includes:
#include "terminal.hpp"


namespace token::reserved {
// Macros:
// Do not use these macros outside of this file!
#define DEFINE_TERMINAL(name, id, token) \
  constexpr Terminal name                \
  {                                      \
    id, TokenType::token                 \
  }

// clang-format off
// Language reserved keywords
namespace keywords {
  DEFINE_TERMINAL(g_function, "function", FUNCTION);
  DEFINE_TERMINAL(g_return,   "return",   RETURN);

  DEFINE_TERMINAL(g_if,   "if",   IF);
  DEFINE_TERMINAL(g_else, "else", ELSE);

  DEFINE_TERMINAL(g_do,    "do",    DO);
  DEFINE_TERMINAL(g_while, "while", WHILE);
  DEFINE_TERMINAL(g_for,   "for",   FOR);
  DEFINE_TERMINAL(g_in,    "in",    IN);

  DEFINE_TERMINAL(g_break,    "break",    BREAK);
  DEFINE_TERMINAL(g_continue, "continue", CONTINUE);

  DEFINE_TERMINAL(g_next, "next", NEXT);
  DEFINE_TERMINAL(g_exit, "exit", EXIT);

  DEFINE_TERMINAL(g_delete, "delete", DELETE);

  DEFINE_TERMINAL(g_print,   "print",   PRINT);
  DEFINE_TERMINAL(g_printf,  "printf",  PRINTF);
  DEFINE_TERMINAL(g_getline, "getline", GETLINE);

  DEFINE_TERMINAL(g_begin, "BEGIN", BEGIN);
  DEFINE_TERMINAL(g_end,   "END",   END);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  // TODO: Make these be generated automagically
  // TODO: Make this a constexpr vector? those have constexpr initializer_list constructor
  constexpr std::array g_keywords{
	g_function, g_return,
	g_if, g_else,
	g_do, g_while, g_for, g_in,
	g_break, g_continue,
	g_next, g_exit,
	g_delete,
	g_print, g_printf, g_getline,
	g_begin, g_end
  };
} // namespace keywords

namespace functions {
  // Builtin functions
  // Arithmetic functions:
  DEFINE_TERMINAL(g_atan2,    "atan2",    BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_cos,      "cos",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_sin,      "sin",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_exp,      "exp",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_log,      "log",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_sqrt,     "sqrt",     BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_int,      "int",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_rand,     "rand",     BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_srand,    "srand",    BUILTIN_FUNCTION);

	// String functions:
  DEFINE_TERMINAL(g_gsub,     "gsub",     BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_index,    "index",    BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_length,   "length",   BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_match,    "match",    BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_split,    "split",    BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_sprintf,  "sprintf",  BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_sub,      "sub",      BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_substr,   "substr",   BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_tolower,  "tolower",  BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_toupper,  "toupper",  BUILTIN_FUNCTION);

	// IO and general functions:
  DEFINE_TERMINAL(g_close,    "close",    BUILTIN_FUNCTION);
  DEFINE_TERMINAL(g_system,   "system",   BUILTIN_FUNCTION);

  // TODO: Use a std::map instead of an array as those have a faster lookup time
  // Then we wont need to loop through them either
  // TODO: Make these be generated automagically
  // TODO: Make this a constexpr vector? those have constexpr initializer_list constructor
  constexpr std::array g_functions{
    g_atan2,
    g_cos,
    g_exp,
    g_log,
    g_sqrt,
    g_int,
    g_rand,
    g_srand,

    g_gsub,
    g_index,
    g_length,
    g_match,
    g_sin,
    g_split,
    g_sprintf,
    g_sub,
    g_substr,
    g_tolower,
    g_toupper,

    g_close,
    g_system
  };
} // namespace functions

// Language reserved symbols
namespace symbols {
  // Braces
  DEFINE_TERMINAL(g_paren_open,     '(', PAREN_OPEN);
  DEFINE_TERMINAL(g_paren_close,    ')', PAREN_CLOSE);
  DEFINE_TERMINAL(g_accolade_open,  '{', ACCOLADE_OPEN);
  DEFINE_TERMINAL(g_accolade_close, '}', ACCOLADE_CLOSE);
  DEFINE_TERMINAL(g_brace_open,     '[', BRACE_OPEN);
  DEFINE_TERMINAL(g_brace_close,    ']', BRACE_CLOSE);

  // Arithmetic operators:
  DEFINE_TERMINAL(g_caret,        '^', CARET);
  DEFINE_TERMINAL(g_plus,         '+', PLUS);
  DEFINE_TERMINAL(g_minus,        '-', MINUS);
  DEFINE_TERMINAL(g_asterisk,     '*', ASTERISK);
  DEFINE_TERMINAL(g_slash,        '/', SLASH);
  DEFINE_TERMINAL(g_percent_sign, '%', PERCENT_SIGN);

  // Assignment variants of Arithmetic operators:
  DEFINE_TERMINAL(g_increment, "++", INCREMENT);
  DEFINE_TERMINAL(g_decrement, "--", DECREMENT);

  // Assignment:
  // TODO: Rename or structure these better in the future?
  DEFINE_TERMINAL(g_power_assignment,    "^=", POWER_ASSIGNMENT);

  DEFINE_TERMINAL(g_multiply_assignment, "*=", MULTIPLY_ASSIGNMENT);
  DEFINE_TERMINAL(g_divide_assignment,   "/=", DIVIDE_ASSIGNMENT);
  DEFINE_TERMINAL(g_modulo_assignment,   "%=", MODULO_ASSIGNMENT);

  DEFINE_TERMINAL(g_add_assignment,      "+=", ADD_ASSIGNMENT);
  DEFINE_TERMINAL(g_subtract_assignment, "-=", SUBTRACT_ASSIGNMENT);

  DEFINE_TERMINAL(g_assignment, '=', ASSIGNMENT);

  // Regex operators:
  DEFINE_TERMINAL(g_ere_match,    '~',  ERE_MATCH);
  DEFINE_TERMINAL(g_ere_no_match, "!~", ERE_NO_MATCH);

  // Logic operators:
  DEFINE_TERMINAL(g_or,  "||", OR);
  DEFINE_TERMINAL(g_and, "&&", AND);

  DEFINE_TERMINAL(g_not,             '!',   NOT);
  DEFINE_TERMINAL(g_less_than,       '<',   LESS_THAN);
  DEFINE_TERMINAL(g_less_than_equal, "<=", LESS_THAN_EQUAL);

  DEFINE_TERMINAL(g_equal,     "==", EQUAL);
  DEFINE_TERMINAL(g_not_equal, "!=", NOT_EQUAL);

  DEFINE_TERMINAL(g_greater_than,       '>',   GREATER_THAN);
  DEFINE_TERMINAL(g_greater_than_equal, ">=", GREATER_THAN_EQUAL);

  // Control flow symbols:
  DEFINE_TERMINAL(g_comma,        ',', COMMA);
  DEFINE_TERMINAL(g_dot,          '.', DOT);
  DEFINE_TERMINAL(g_question_mark, '?', QUESTION_MARK);
  DEFINE_TERMINAL(g_colon,        ':', COLON);
  DEFINE_TERMINAL(g_semicolon,    ';', SEMICOLON);

  // Output redirection:
  DEFINE_TERMINAL(g_trunc,  '>',  TRUNC);
  DEFINE_TERMINAL(g_append, ">>", APPEND);
  DEFINE_TERMINAL(g_pipe,   '|',  PIPE);

  // Miscellaneous operators:
  DEFINE_TERMINAL(g_dollar_sign,  '$',  DOLLAR_SIGN);
  DEFINE_TERMINAL(g_newline,  '\n', NEWLINE);

  constexpr std::array g_single_symbols{
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
	g_question_mark,
	g_colon,
	g_semicolon,

	g_trunc,
	g_pipe,

	g_dollar_sign,
	g_newline
  };

  constexpr std::array g_multi_symbols{
	g_increment,
	g_decrement,

	g_power_assignment,

	g_multiply_assignment,
	g_divide_assignment,
	g_modulo_assignment,

	g_add_assignment,
	g_subtract_assignment,

	g_ere_no_match,

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
	constexpr char g_double_quote{'"'};
	constexpr char g_backslash{'\\'};
} // namespace none
} // namespace symbols
} // namespace reserved
// clang-format on

#endif // AWX_TOKEN_RESERVED_RESERVED_HPP
