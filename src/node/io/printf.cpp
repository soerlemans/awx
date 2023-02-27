#include "printf.hpp"

#include <utility>


using namespace nodes::io;

Printf::Printf(NodeListPtr&& t_params)
  :  m_params{std::forward<NodeListPtr>(t_params)}
{}

auto Printf::params() -> NodeListPtr&
{
  return m_params;
}

auto Printf::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
