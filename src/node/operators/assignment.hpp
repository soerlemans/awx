#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


enum AssignmentOp {
  POWER = 0,

  MULTIPLY,
  DIVIDE,
  MODULO,

  ADD,
  SUBTRACT,

  REGULAR
};

namespace nodes::operators {
class Assignment : public BinaryOperator {
  private:
  AssignmentOp m_op;

  public:
  Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Assignment() override = default;
};
} // namespace nodes::operators

#endif // ASSIGNMENT_HPP
