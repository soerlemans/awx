#include "unary_operator.hpp"

using namespace operators;


UnaryOperator::UnaryOperator(Precedence t_precedence,
                             NodePointer&& t_stmnt)
  : Expression{t_precedence}, m_first{std::forward<NodePointer>(t_stmnt)}
{}

auto UnaryOperator::first() -> NodePointer&
{
  return m_first;
}

UnaryOperator::~UnaryOperator()
{}
