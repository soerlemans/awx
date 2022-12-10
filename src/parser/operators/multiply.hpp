#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "operators.hpp"
#include "binary_operator.hpp"


class operators::Multiply : public operators::BinaryOperator {
public:
  Multiply(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Multiply();
};

#endif // MULTIPLY_H
