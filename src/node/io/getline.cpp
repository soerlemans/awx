#include "getline.hpp"

#include <utility>


using namespace nodes::io;

Getline::Getline(NodePtr&& t_var)
  : Node{NodeType::IO}, m_var{std::forward<NodePtr>(t_var)}
{}

auto Getline::accept(NodeVisitor t_visitor) -> void
{}

auto Getline::print() const -> void
{}

Getline::~Getline()
{}
