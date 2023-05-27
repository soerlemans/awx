#include "do_while.hpp"

// STL Includes:
#include <utility>


using namespace visitor;
using namespace node::control;

DoWhile::DoWhile(NodePtr&& t_condition, NodeListPtr&& t_body)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}


auto DoWhile::condition() -> NodePtr&
{
  return m_condition;
}

auto DoWhile::body() -> NodeListPtr&
{
  return m_body;
}

auto DoWhile::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
