#include "exit.hpp"


using namespace node::control;

using namespace visitor;

Exit::Exit(NodePtr&& t_expr): m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Exit::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
