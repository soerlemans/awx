#include "delete.hpp"

using namespace operators;


Delete::Delete(NodePtr&& t_array)
  : Node{NodeType::EXPRESSION}, m_array{std::forward<NodePtr>(t_array)}
{}

auto Delete::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{}

auto Delete::print() const -> void
{}

Delete::~Delete()
{}
