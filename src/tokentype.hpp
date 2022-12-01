#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "types.hpp"

// Enum definitions:
namespace TokenType {
enum : u16 {
  IDENTIFIER,
};

enum class Keyword : u16 {
  NOT_KEYWORD,
  FUNCTION_KEYWORD,
  IF_KEYWORD,
  ELSE_KEYWORD,
  DO_KEYWORD,
  WHILE_KEYWORD,
  FOR_KEYWORD,
  IN_KEYWORD,
};

enum class Type : u16 {
  INTEGER,
  FLOAT,
  HEX,
  STRING,
  REGEX,
};

enum class Brace : u16 {
  PAREN_OPEN,
  PAREP_CLOSE,

  ACCOLADE_OPEN,
  ACCOLADE_CLOSE,

  BRACE_OPEN,
  BRACE_CLOSE,
};

enum class Num : u16 {
  // Numeric Tokens:
  INCREMENT,
  DECREMENT,

  EXPONENT,
  PLUS,
  MINUS,

  MULTIPLIER,
  DIVIDER,
  MODULUS,

  EXPONENT_ASSIGNMENT,
  PLUS_ASSIGNMENT,
  MINUS_ASSIGNMENT,

  MULTIPLICATION_ASSIGNEMNT,
  DIVISION_ASSIGNMENT,
  ADDITION_ASSIGNMENT,
  SUBTRACTION_ASSIGNMENT,
  ASSIGNMENT,
};

enum class Regex : u16 {
  ERE_MATCH,
  NOT_ERE_MATCH,
};

enum class Logical : u16 {
  NOT,

  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  AND,
  OR,
};

enum class ControlFlow : u16 {
  COMMA,
  QUESTIONMARK,
  COLON,
  SEMICOLON,
};

enum class Miscellaneous : u16 {
  DOLLAR_SIGN,
  END_OF_LINE,
};
}; // namespace TokenType

#endif // TOKENTYPE_H
