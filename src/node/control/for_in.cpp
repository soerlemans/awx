#include "for_in.hpp"


using namespace nodes::control;

ForIn::ForIn(NodePtr&& t_identifier, NodePtr&& t_array, NodeListPtr&& t_body)
  : m_identifier{std::forward<NodePtr>(t_identifier)},
    m_array{std::forward<NodePtr>(t_array)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto ForIn::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
