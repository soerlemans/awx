#ifndef DIVIDE_OPERATOR_H
#define DIVIDE_OPERATOR_H

#include "binary_operator.hpp"

class DivideOperator : public BinaryOperator {
public:
  DivideOperator(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~DivideOperator();
};

#endif // DIVIDE_OPERATOR_H
