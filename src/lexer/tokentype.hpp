#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "../types.hpp"


// TODO: Move this function somewhere applicable
template<typename Enumeration>
auto enum2underlying_type(Enumeration const value) ->
  typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// Enum definitions:
enum class TokenType : u16 {
  UNKNOWN = 0,
  NONE,

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

  // Types:
  INTEGER,
  FLOAT,
  HEX,
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

  EXPONENT,
  PLUS,
  MINUS,

  MULTIPLIER,
  SLASH,
  MODULUS,

  EXPONENT_ASSIGNMENT,
  PLUS_ASSIGNMENT,
  MINUS_ASSIGNMENT,

  MULTIPLICATION_ASSIGNMENT,
  DIVISION_ASSIGNMENT,
  MODULO_ASSIGNMENT,
  ADDITION_ASSIGNMENT,
  SUBTRACTION_ASSIGNMENT,

  // REGEX Tokens:
  ERE_MATCH,
  NOT_ERE_MATCH,

  // Logical Tokens:
  NOT,

  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  AND,
  OR,

  // Control flow Tokens:
  COMMA,
  DOT,
  QUESTIONMARK,
  COLON,
  SEMICOLON,

  // Miscellaneous:
  DOLLAR_SIGN,
  VERTICAL_BAR,
  END_OF_LINE,
};

// Functions:
namespace tokentype {
auto is_int(const TokenType t_tokentype) -> bool;
}; // namespace tokentype

#endif // TOKENTYPE_H