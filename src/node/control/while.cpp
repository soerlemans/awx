#include "while.hpp"


#include <utility>


using namespace nodes::control;

While::While(NodePtr&& t_condition, NodePtr&& t_body)
  : Node{NodeType::CONTROL_STATEMENT},
    m_condition{std::forward<NodePtr>(t_condition)},
    m_body{std::forward<NodePtr>(t_body)}
{}

auto While::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

While::~While()
{}
