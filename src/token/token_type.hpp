#ifndef AWX_TOKEN_TOKEN_TYPE_HPP
#define AWX_TOKEN_TOKEN_TYPE_HPP

#include "../types.hpp"


namespace token {
// Enums:
enum class TokenType {
  NONE = 0,

  // Identifiers:
  IDENTIFIER,
  FUNCTION_IDENTIFIER,

  // Keywords:
  FUNCTION,
  RETURN,

  // Branching keywords:
  IF,
  ELSE,

  // Loop keywords:
  DO,
  WHILE,
  FOR,
  IN,

  // Flow control keywords:
  BREAK,
  CONTINUE,

  // Rule control keywords:
  NEXT,
  EXIT,

  // Delete keyword:
  DELETE,

  // IO keywords:
  PRINT,
  PRINTF,
  GETLINE,

  // Action keywords:
  BEGIN,
  END,

  // Builtin function type:
  BUILTIN_FUNCTION,

  // TYPES:
  INTEGER,
  HEX,
  FLOAT,
  STRING,
  REGEX,

  // Brace types:
  PAREN_OPEN,
  PAREN_CLOSE,

  ACCOLADE_OPEN,
  ACCOLADE_CLOSE,

  BRACE_OPEN,
  BRACE_CLOSE,

  // Numeric Tokens:
  INCREMENT,
  DECREMENT,

  CARET,
  PLUS,
  MINUS,

  ASTERISK,
  SLASH,
  PERCENT_SIGN,

  // Assignment:
  POWER_ASSIGNMENT,

  MULTIPLY_ASSIGNMENT,
  DIVIDE_ASSIGNMENT,
  MODULO_ASSIGNMENT,

  ADD_ASSIGNMENT,
  SUBTRACT_ASSIGNMENT,

  ASSIGNMENT,

  // REGEX Tokens:
  ERE_MATCH,
  ERE_NO_MATCH,

  // Comparison Tokens:
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  // Logical Tokens:
  NOT,

  AND,
  OR,

  // Control flow Tokens:
  COMMA,
  DOT,
  QUESTION_MARK,
  COLON,
  SEMICOLON,

  // Output redirection:
  TRUNC,
  APPEND,
  PIPE,

  // Miscellaneous:
  DOLLAR_SIGN,
  NEWLINE, // 58
};
} // namespace token

#endif // AWX_TOKEN_TOKEN_TYPE_HPP
