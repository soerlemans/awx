#include "unary_operator.hpp"

using namespace nodes::operators;


UnaryOperator::UnaryOperator(Precedence t_precedence, NodePtr&& t_stmnt)
  : Expression{t_precedence}, m_first{std::forward<NodePtr>(t_stmnt)}
{}

auto UnaryOperator::first() -> NodePtr&
{
  return m_first;
}

UnaryOperator::~UnaryOperator()
{}
