#ifndef OPERATORS_H
#define OPERATORS_H


// All Operator classes are part of this namespace
// These forward declarations are also used by StatementVisitor
// To declare its overload functions for visit()
namespace operators {
  // Abstract Base classes:
  class UnaryOperator;
  class BinaryOperator;
  class TrinaryOperator;

  // UnaryOperator derived classes:
  class PrefixIncrement;
  class PrefixDecrement;

  class PostfixIncrement;
  class PostfixDecrement;

  // Logical:
  class Not;

  // BinaryOperator derived classes:
  // Arithmetic:
  class Power;

  class Multiply;
  class Divide;
  class Modulo;

  class Add;
  class Subtract;

  // String operations:
  class StringConcatenation;

  // Comparison:
  class LessThan;
  class LessThanEqual;

  class NotEqual;
  class Equal;

  class GreaterThan;
  class GreaterThanEqual;

  // ERE:
  class EreMatch;
  class EreNonMatch;

  // Array operations:
  class ArrayMembership;
  class ArrayMultiDimensionalMembership;

  // Logical:
  class And;
  class Or;

  // Assignment:
  class PowerAssignment;

  class MultiplyAssignment;
  class DivideAssignment;
  class ModuloAssignment;

  class AddAssignment;
  class SubtractAssignment;

  class Assignment;
};

#endif // OPERATORS_H
