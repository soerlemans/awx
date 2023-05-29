#include "field_reference.hpp"


using namespace node::lvalue;

using namespace visitor;

FieldReference::FieldReference(NodePtr&& t_expr)
  : m_expr{std::forward<NodePtr>(t_expr)}
{}

auto FieldReference::expr() -> NodePtr&
{
  return m_expr;
}

