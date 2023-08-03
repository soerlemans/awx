#include "for_in.hpp"


using namespace node::control;

using namespace visitor;

ForIn::ForIn(NodePtr&& t_identifier, NodePtr&& t_array, NodeListPtr&& t_body)
  : m_identifier{std::forward<NodePtr>(t_identifier)},
    m_array{std::forward<NodePtr>(t_array)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto ForIn::identifier() -> NodePtr&
{
  return m_identifier;
}

auto ForIn::array() -> NodePtr&
{
  return m_array;
}

auto ForIn::body() -> NodeListPtr&
{
  return m_body;
}
