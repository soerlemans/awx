#include "recipe.hpp"
#include <stdexcept>


using namespace node::recipes;

using namespace visitor;

Recipe::Recipe(NodePtr&& t_pattern, NodePtr&& t_body)
  : m_pattern{std::forward<NodePtr>(t_pattern)},
    m_body{std::forward<NodePtr>(t_body)}
{
  // TODO: Improve! For now we just throw but we want better error handling
  if(!m_body)
    throw std::runtime_error{"Toplevel blocks must have a body"};
}

auto Recipe::pattern() -> NodePtr&
{
  return m_pattern;
}

auto Recipe::body() -> NodePtr&
{
  return m_body;
}

auto Recipe::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
