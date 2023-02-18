#include "if.hpp"

#include <utility>


using namespace nodes::control;

If ::If(NodePtr&& t_condition, NodePtr&& t_then)
  : Node{NodeType::CONTROL_STATEMENT},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_then{std::forward<NodePtr>(t_then)}
{}


If::If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else)
  : If{std::forward<NodePtr>(t_condition), std::forward<NodePtr>(t_then)}
{}

auto If::then() -> NodePtr&
{
  return m_then;
}

auto If::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
