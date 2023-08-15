#include "recipe.hpp"
#include <stdexcept>


using namespace node::recipes;

using namespace visitor;

Recipe::Recipe(NodePtr&& t_condition, NodePtr&& t_body)
  : m_condition{std::forward<NodePtr>(t_condition)},
    m_body{std::forward<NodePtr>(t_body)}
{
  // TODO: Improve! For now we just throw but we want better error handling
  if(!m_body)
    throw std::runtime_error{"Toplevel blocks must have a body"};
}

auto Recipe::condition() -> NodePtr&
{
  return m_condition;
}

auto Recipe::body() -> NodePtr&
{
  return m_body;
}
