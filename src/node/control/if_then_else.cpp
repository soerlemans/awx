#include "if_then_else.hpp"

#include <utility>


using namespace nodes::control;

IfThenElse::IfThenElse(NodePtr&& t_then, NodePtr&& t_else)
  : Node{NodeType::CONTROL_STATEMENT},
    m_then{std::forward<NodePtr>(t_then)},
    m_else{std::forward<NodePtr>(t_else)}
{}

auto IfThenElse::accept(NodeVisitor t_visitor) -> void
{}

auto IfThenElse::print() const -> void
{}

IfThenElse::~IfThenElse()
{}
