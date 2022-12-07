#ifndef EXPRESSIONTYPE_H
#define EXPRESSIONTYPE_H

#include "types.hpp"


template<typename Enumeration>
auto enum2underlying_type(Enumeration const value) ->
  typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// Enum definitions:
enum class ExpressionType : u16 {
  UNKNOWN = 0,
  NONE,

  // Types:
  INTEGER,
  FLOAT,
  STRING,
  REGEX,
  ARRAY,

  // Unary expressions:
  FIELD_REFERENCE,

  POSTFIX_INCREMENT,
  POSTFIX_DECREMENT,

  PREFIX_INCREMENT,
  PREFIX_DECREMENT,

  LOGICAL_NOT,
  UNARY_PLUS,
  UNARY_MINUS,

  // Binary expressions:
  EXPONENTATION,

  MULTIPLICATION,
  DIVISION,
  MODULUS,

  ADDITION,
  SUBTRACTION,

  STRING_CONCATIONATION,

  LESS_THAN,
  LESS_THAN_EQUAL,

  NOT_EQUAL,
  EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  ERE_MATCH,
  NOT_ERE_MATCH,

  IN_ARRAY,
  IN_MULTIDIMENSIONAL_ARRAY,

  AND,
  OR,

  EXPONENTATION_ASSIGNMENT,

  MULTIPLICATION_ASSIGNMENT,
  DIVISION_ASSIGNMENT,
  MODULUS_ASSIGNMENT,

  ADDITION_ASSIGNMENT,
  SUBTRACTION_ASSIGNMENT,

  ASSIGNMENT,

  // Trinary expression:
  CONDITIONAL_ASSIGNMENT,

  // Keyword:
  FUNCTION,
  FUNCTION_CALL,

  // Control statements:
  IF,
  DO,
  WHILE,
  FOR,

  // Miscellaneous:
  GROUPING,
  SUBSCRIPT,
};

#endif // EXPRESSIONTYPE_H
