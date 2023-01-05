#include "field_reference.hpp"


FieldReference::FieldReference(NodePtr&& t_expr)
  : Node{NodeType::VARIABLE}, m_expr{std::forward<NodePtr>(t_expr)}
{}

auto FieldReference::accept(NodeVisitor t_visitor) -> void
{}

auto FieldReference::print() const -> void
{}

FieldReference::~FieldReference()
{}
