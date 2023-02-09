#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
enum class ArithmeticOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT
};

class Arithmetic : public BinaryOperator {
  private:
  ArithmeticOp m_op;

  public:
  Arithmetic(ArithmeticOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Arithmetic() override = default;
};
} // namespace nodes::operators

#endif
