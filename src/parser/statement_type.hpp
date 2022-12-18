#ifndef STATEMENT_TYPE_H
#define STATEMENT_TYPE_H

#include "../types.hpp"


// Enum definitions:
enum class StatementType : u16 {
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

  NOT,
  PLUS,
  MINUS,

  // Binary expressions:
  // Arithmetic:
  POWER,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT,

  // String operations:
  STRING_CONCATIONATION,

  // Comparisons:
  LESS_THAN,
  LESS_THAN_EQUAL,

  NOT_EQUAL,
  EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,

  // Regex match:
  ERE_MATCH,
  NOT_ERE_MATCH,

  // Array operations:
  ARRAY_MEMBERSHIP,
  ARRAY_MULTIDIMENSIONAL_MEMBERSHIP,

  // Logical Statements:
  AND,
  OR,

  // Assignment:
  POWER_ASSIGNMENT,

  MULTIPLY_ASSIGNMENT,
  DIVIDE_ASSIGNMENT,
  MODULO_ASSIGNMENT,

  ADD_ASSIGNMENT,
  SUBTRACT_ASSIGNMENT,

  ASSIGNMENT,

  // Trinary expression:
  CONDITIONAL,

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

#endif // STATEMENT_TYPE_H
