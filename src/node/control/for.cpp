#include "for.hpp"

#include "../list.hpp"


using namespace node::control;

For::For(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
         NodeListPtr&& t_body)
  : m_init{std::forward<NodePtr>(t_init)},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_expr{std::forward<NodePtr>(t_expr)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto For::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
