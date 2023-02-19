#include "return.hpp"


using namespace nodes::control;

Return::Return(NodePtr&& t_expr)
  : Node{NodeType::CONTROL_STATEMENT}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Return::expr() -> NodePtr&
{
  return m_expr;
}

auto Return::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
