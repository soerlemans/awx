#include "field_reference.hpp"


using namespace nodes::lvalue;

FieldReference::FieldReference(NodePtr&& t_expr)
  : Node{NodeType::VARIABLE}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto FieldReference::expr() -> NodePtr&
{
  return m_expr;
}

auto FieldReference::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

FieldReference::~FieldReference()
{}
