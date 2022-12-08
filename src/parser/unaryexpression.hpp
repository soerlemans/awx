#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

#include "expression.hpp"


class UnaryExpression : public Expression {
protected:
  ExpressionPointer m_left;

public:
  explicit UnaryExpression(ExpressionType t_exprtype, Expression&& t_expr);

  auto left() const -> Expression;

  virtual ~UnaryExpression();
};

#endif // UNARYEXPRESSION_H
