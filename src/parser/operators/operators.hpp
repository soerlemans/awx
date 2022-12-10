#ifndef OPERATORS_H
#define OPERATORS_H


// All Operator classes are part of this namespace
// These forward declarations are also used by StatementVisitor
// To declare its overload functions for visit()
namespace operators {
  // Abstract Base classes:
  class UnaryOperator;
  class BinaryOperator;

  // UnaryOperator derived classes:
  class PrefixIncrement;
  class PrefixDecrement;

  class PostfixIncrement;
  class PostfixDecrement;

  // BinaryOperator derived classes:
  class Power;
  class Multiply;
  class Divide;
  class Add;
  class Subtract;
};

#endif // OPERATORS_H
