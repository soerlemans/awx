#ifndef POWER_H
#define POWER_H

#include "operators.hpp"
#include "binary_operator.hpp"


class operators::Power : public operators::BinaryOperator {
public:
  Power(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Power();
};

#endif // POWER_H
