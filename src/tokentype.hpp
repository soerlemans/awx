#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "types.hpp"

// Enum definitions:
enum class TokenType : u32 {
  UNKNOWN = 0,

  // Identifiers:
  IDENTIFIER,

  // Keywords:
  FUNCTION_KEYWORD,
  IF_KEYWORD,
  ELSE_KEYWORD,
  DO_KEYWORD,
  WHILE_KEYWORD,
  FOR_KEYWORD,
  IN_KEYWORD,

  // Types:
  STRING,
  NUMERIC,

  // Brace types:
  PAREN_OPEN = '(',
  PAREP_CLOSE = ')',

  ACCOLADE_OPEN = '{',
  ACCOLADE_CLOSE = '}',

  BRACE_OPEN = '[',
  BRACE_CLOSE = ']',

  // Quotes:
  SINGLE_QUOTE = '\'',
  DOUBLE_QUOTE = '"',

  // Numeric Tokens:
  INCREMENT,
  DECREMENT,

  EXPONENT = '^',
  PLUS = '+',
  MINUS = '-',

  MULTIPLIER = '*',
  DIVIDER = '/',
  MODULUS = '%',

  EXPONENT_ASSIGNMENT,
  PLUS_ASSIGNMENT,
  MINUS_ASSIGNMENT,

  MULTIPLICATION_ASSIGNEMNT,
  DIVISION_ASSIGNMENT,
  ADDITION_ASSIGNMENT,
  SUBTRACTION_ASSIGNMENT,
  ASSIGNMENT = '=',

  // REGEX Tokens:
  ERE_MATCH = '~',
  NOT_ERE_MATCH,

  // Logical Tokens:
  NOT = '!',

  LESS_THAN = '<',
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN = '>',
  GREATER_THAN_EQUAL,

  AND,
  OR,

  // Miscellaneous:
  COMMA = ',',
  QUESTIONMARK = '?',
  COLON = ':',
  SEMICOLON = ';',

  DOLLAR_SIGN = '$',

  WHITESPACE,
  EOL = '\n',
  EOF,
};

#endif // TOKENTYPE_H