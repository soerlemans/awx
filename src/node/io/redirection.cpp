#include "redirection.hpp"


using namespace node::io;

Redirection::Redirection(RedirectionOp t_op, NodePtr&& t_left,
                         NodePtr&& t_right)
  : m_op{t_op},
    m_left{std::forward<NodePtr>(t_left)},
    m_right{std::forward<NodePtr>(t_right)}
{}

auto Redirection::left() -> NodePtr&
{
  return m_left;
}

auto Redirection::right() -> NodePtr&
{
  return m_right;
}

auto Redirection::op() const -> RedirectionOp
{
  return m_op;
}

auto Redirection::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
