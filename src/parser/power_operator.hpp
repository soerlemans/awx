#ifndef POWER_OPERATOR_H
#define POWER_OPERATOR_H

#include "binary_operator.hpp"


class PowerOperator : public BinaryOperator {
public:
  PowerOperator(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PowerOperator();
};

#endif // POWER_OPERATOR_H
