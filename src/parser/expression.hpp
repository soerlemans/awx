#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <type_traits>

#include "expressiontype.hpp"


// Forward declarations:
class Expression;

// Aliases:
using ExpressionPointer = std::unique_ptr<Expression>;

// Base expression class:
class Expression {
protected:
  ExpressionType m_expressiontype;

public:
  explicit Expression(ExpressionType t_expressiontype);

  auto type() -> ExpressionType;

  virtual ~Expression();
};

#endif // EXPRESSION_H
