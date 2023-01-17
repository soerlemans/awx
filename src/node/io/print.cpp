#include "print.hpp"

#include <utility>


using namespace nodes::io;

Print::Print(NodePtr&& t_expr)
  : Node{NodeType::IO}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Print::accept(NodeVisitor t_visitor) -> void
{}

auto Print::print() const -> void
{}

Print::~Print()
{}
