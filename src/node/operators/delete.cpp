#include "delete.hpp"


using namespace nodes::operators;

Delete::Delete(NodePtr&& t_array)
  : Node{NodeType::EXPRESSION}, m_array{std::forward<NodePtr>(t_array)}
{}

auto Delete::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
