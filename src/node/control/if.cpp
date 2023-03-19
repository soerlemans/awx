#include "if.hpp"

#include <utility>


using namespace node::control;

using namespace visitor;

If ::If(NodePtr&& t_condition, NodePtr&& t_then)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_then{std::forward<NodePtr>(t_then)}
{}


If::If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else)
  : If{std::forward<NodePtr>(t_condition), std::forward<NodePtr>(t_then)}
{}

auto If::then() -> NodePtr&
{
  return m_then;
}

auto If::alt() -> NodePtr&
{
  return m_else;
}

auto If::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
