#include "recipe.hpp"


using namespace nodes::recipes;

Recipe::Recipe(NodePtr&& t_pattern, NodePtr&& t_body)
  : 
    m_pattern{std::forward<NodePtr>(t_pattern)},
    m_body{std::forward<NodePtr>(t_body)}
{}

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
