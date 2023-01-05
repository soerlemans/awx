#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include "../types.hpp"


// Enum definitions:
enum class TokenType : u16 {
  NONE = 0,

  // Identifiers:
  IDENTIFIER,

  // Keywords:
  FUNCTION,
  RETURN,

  IF,
  ELSE,

  DO,
  WHILE,
  FOR,
  IN,

  // Function keywords:
  PRINT,
  PRINTF,

  // Action keywords:
  BEGIN,
  END,

  // Types:
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

  // Assignment:
  ASSIGNMENT,

  // Numeric Tokens:
  INCREMENT,
  DECREMENT,

  POWER,
  PLUS,
  MINUS,

  ASTERISK,
  SLASH,
  PERCENT_SIGN,

  POWER_ASSIGNMENT,
  PLUS_ASSIGNMENT,
  MINUS_ASSIGNMENT,

  MULTIPLY_ASSIGNMENT,
  DIVIDE_ASSIGNMENT,
  MODULO_ASSIGNMENT,
  ADD_ASSIGNMENT,
  SUBTRACT_ASSIGNMENT,

  // REGEX Tokens:
  ERE_MATCH,
  NOT_ERE_MATCH,

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
  QUESTIONMARK,
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

#endif // TOKEN_TYPE_H
