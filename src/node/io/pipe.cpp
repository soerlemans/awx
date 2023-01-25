#include "pipe.hpp"

#include <utility>


using namespace nodes::io;

Pipe::Pipe(NodePtr&& t_expr, NodePtr&& t_getline)
  : Node{NodeType::IO},
    m_expr{std::forward<NodePtr>(t_expr)},
    m_getline{std::forward<NodePtr>(t_getline)}
{}

auto Pipe::accept(NodeVisitor t_visitor) -> void
{}

auto Pipe::print() const -> void
{}

Pipe::~Pipe()
{}
