#ifndef OPERATORS_H
#define OPERATORS_H


// All Operator classes are part of this namespace
// These forward declarations are also used by NodeVisitor
// To declare its overload functions for visit()
namespace operators {
// Abstract Base classes:
class UnaryOperator;
class BinaryOperator;
class TrinaryOperator;

class DynamicOperator;

// UnaryOperator derived classes:
class Increment;
class Decrement;

// Logical:
class Not;

// BinaryOperator derived classes:
// Arithmetic:
class Arithmetic;

// String operations:
class StringConcatenation;

// Comparison:
class Comparison;

// ERE:
class EreMatch;
class EreNonMatch;

// Array operations:
class ArrayMembership;
class ArrayMultiDimensionalMembership;

// Delete:
class Delete;

// Logical:
class And;
class Or;

// Assignment:
class Assignment;

// TrinaryOperator derived classes:
class Conditional;

// DynamicOperators:
class FunctionDefinition;
class FunctionCall;
}; // namespace operators

#endif // OPERATORS_H
