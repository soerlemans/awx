#include "unary_operator.hpp"

using namespace node::operators;

using namespace visitor;


UnaryOperator::UnaryOperator(Precedence t_precedence, NodePtr&& t_left)
  : Expression{t_precedence}, m_left{std::forward<NodePtr>(t_left)}
{}

auto UnaryOperator::left() -> NodePtr&
{
  return m_left;
}
