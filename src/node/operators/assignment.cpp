#include "assignment.hpp"


using namespace node::operators;

using namespace visitor;

Assignment::Assignment(AssignmentOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ASSIGNMENT, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
{}

auto Assignment::op() const -> AssignmentOp
{
  return m_op;
}

auto Assignment::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
