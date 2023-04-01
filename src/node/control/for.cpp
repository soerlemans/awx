#include "for.hpp"

#include "../list.hpp"


using namespace node::control;

using namespace visitor;

For::For(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
         NodeListPtr&& t_body)
  : m_init{std::forward<NodePtr>(t_init)},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_expr{std::forward<NodePtr>(t_expr)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto For::init() -> NodePtr&
{
  return m_init;
}

auto For::condition() -> NodePtr&
{
  return m_condition;
}

auto For::expr() -> NodePtr&
{
  return m_expr;
}

auto For::body() -> NodeListPtr&
{
  return m_body;
}

auto For::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
