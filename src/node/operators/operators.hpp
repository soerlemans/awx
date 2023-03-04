#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "../nodes.hpp"

// All Operator classes are part of this namespace
// These forward declarations are also used by NodeVisitor
// To declare its overload functions for visit()
namespace nodes::operators {
// Abstract Base classes:
class UnaryOperator;
class BinaryOperator;

// UnaryOperator derived classes:
class UnaryPrefix;
class Grouping;
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

// ERE Match:
class Match;

// Array ops:
class Membership;

// Delete:
class Delete;

// Logical:
class And;
class Or;

// Assignment:
class Assignment;

// Trinary operator:
class Ternary;
} // namespace nodes::operators

#endif // OPERATORS_HPP
