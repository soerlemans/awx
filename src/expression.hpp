#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <list>
#include <type_traits>

#include "expressiontype.hpp"


// Forward declarations:
class Expression;

// Concepts:
template<typename T>
concept DerivedFromExpression = std::is_base_of<Expression, T>::value
  && !std::same_as<T, Expression>;

// Aliases:
using ExpressionPointer = std::unique_ptr<Expression>;
using ExpressionList = std::list<std::unique_ptr<Expression>>;

// Abstract base expression class
class Expression {
protected:
  ExpressionType m_expressiontype;

public:
  explicit Expression(ExpressionType t_expressiontype);

  auto type() -> ExpressionType;

  virtual ~Expression();
};

#endif // EXPRESSION_H
