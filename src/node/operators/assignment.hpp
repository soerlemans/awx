#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

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

class operators::Assignment : public operators::BinaryOperator {
  private:
  AssignmentOp m_op;

  public:
  Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Assignment();
};

#endif // ASSIGNMENT_H
