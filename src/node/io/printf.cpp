#include "printf.hpp"

#include <utility>


using namespace nodes::io;

Printf::Printf(NodePtr&& t_expr)
  : Node{NodeType::IO}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Printf::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

Printf::~Printf()
{}
