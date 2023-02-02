#include "if.hpp"

#include <utility>


using namespace nodes::control;

If::If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else)
  : Node{NodeType::CONTROL_STATEMENT},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_then{std::forward<NodePtr>(t_then)},
    m_else{std::forward<NodePtr>(t_else)}
{}

auto If::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

If::~If()
{}
