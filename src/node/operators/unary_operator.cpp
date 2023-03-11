#include "unary_operator.hpp"

using namespace node::operators;


UnaryOperator::UnaryOperator(Precedence t_precedence, NodePtr&& t_first)
  : Expression{t_precedence}, m_first{std::forward<NodePtr>(t_first)}
{}

auto UnaryOperator::first() -> NodePtr&
{
  return m_first;
}
