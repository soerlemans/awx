#ifndef MULTIPLY_OPERATOR_H
#define MULTIPLY_OPERATOR_H

#include "binary_operator.hpp"


class MultiplyOperator : public BinaryOperator {
public:
  MultiplyOperator(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~MultiplyOperator();
};

#endif // MULTIPLY_OPERATOR_H
