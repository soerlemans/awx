#include "printf.hpp"

#include <utility>


using namespace nodes::io;

Printf::Printf(NodePtr&& t_expr)
  : Node{NodeType::IO}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto Printf::accept(NodeVisitor t_visitor) -> void
{}

auto Printf::print() const -> void
{}

Printf::~Printf()
{}
