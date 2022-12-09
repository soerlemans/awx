#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "unary_operator.hpp"

class BinaryOperator : public UnaryOperator {
  protected:
  StatementPointer m_right;

  public:
  explicit BinaryOperator(StatementType t_stmnttype, StatementPointer&& t_left,
                          StatementPointer&& t_right);

  auto right() const -> Statement;

  virtual ~BinaryOperator();
};
#endif // BINARY_OPERATOR_H
