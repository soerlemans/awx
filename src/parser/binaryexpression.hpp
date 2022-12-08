#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "unaryexpression.hpp"

class BinaryExpression : public UnaryExpression {
protected:
  ExpressionPointer m_right;

public:
  explicit BinaryExpression(ExpressionType t_exprtype, Expression&& t_left, Expression&& t_right);

  auto right() const -> Expression;

  virtual ~BinaryExpression();
};
#endif // BINARYEXPRESSION_H
