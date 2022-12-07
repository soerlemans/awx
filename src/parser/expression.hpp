#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <list>
#include <type_traits>

#include "expressiontype.hpp"


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
