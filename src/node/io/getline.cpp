#include "getline.hpp"

#include <utility>


using namespace nodes::io;

Getline::Getline(NodePtr&& t_var): m_var{std::forward<NodePtr>(t_var)}
{}

auto Getline::var() -> NodePtr&
{
  return m_var;
}

auto Getline::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
