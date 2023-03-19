#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
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

	auto op() -> ArithmeticOp;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Arithmetic() override = default;
};
} // namespace node::operators

#endif
