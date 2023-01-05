#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "binary_operator.hpp"
#include "operators.hpp"


enum class ArithmeticOperation {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT
};

class operators::Arithmetic : public operators::BinaryOperator {
  private:
  ArithmeticOperation m_operation;

  public:
  Arithmetic(ArithmeticOperation t_operation, NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Arithmetic();
};

#endif
