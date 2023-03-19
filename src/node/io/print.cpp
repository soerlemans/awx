#include "print.hpp"

#include <utility>


using namespace node::io;

using namespace visitor;

Print::Print(NodeListPtr&& t_params)
  : m_params{std::forward<NodeListPtr>(t_params)}
{}

auto Print::params() -> NodeListPtr&
{
  return m_params;
}

auto Print::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
