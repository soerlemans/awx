#include "for_in.hpp"


using namespace nodes::control;

ForIn::ForIn(NodePtr&& t_condition, NodeListPtr&& t_body)
  : Node{NodeType::CONTROL_STATEMENT},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto ForIn::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
