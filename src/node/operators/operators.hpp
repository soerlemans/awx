#ifndef OPERATORS_H
#define OPERATORS_H

#include "../nodes.hpp"

// All Operator classes are part of this namespace
// These forward declarations are also used by NodeVisitor
// To declare its overload functions for visit()
namespace nodes::operators {
// Abstract Base classes:
class UnaryOperator;
class BinaryOperator;

class DynamicOperator;

// UnaryOperator derived classes:
class UnaryPrefix;
class Increment;
class Decrement;

// Logical:
class Not;

// BinaryOperator derived classes:
// Arithmetic:
class Arithmetic;

// String ops:
class StringConcatenation;

// Comparison:
class Comparison;

// ERE:
class EreMatch;
class EreNonMatch;

// Array ops:
class ArrayMembership;

// Delete:
class Delete;

// Logical:
class And;
class Or;

// Assignment:
class Assignment;

// Trinary operator:
class Ternary;

// DynamicOperators:
class FunctionDefinition;
class FunctionCall;
}; // namespace nodes::operators

#endif // OPERATORS_H
