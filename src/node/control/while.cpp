#include "while.hpp"

#include <utility>


using namespace node::control;

using namespace visitor;

While::While(NodePtr&& t_condition, NodeListPtr&& t_body)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}


auto While::condition() -> NodePtr&
{
  return m_condition;
}

auto While::body() -> NodeListPtr&
{
  return m_body;
}

auto While::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
