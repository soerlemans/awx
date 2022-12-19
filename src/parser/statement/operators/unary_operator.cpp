#include "unary_operator.hpp"

using namespace operators;


UnaryOperator::UnaryOperator(Precedence t_precedence,
                             StatementPointer&& t_stmnt)
  : Expression{t_precedence}, m_first{std::forward<StatementPointer>(t_stmnt)}
{}

auto UnaryOperator::first() -> StatementPointer&
{
  return m_first;
}

UnaryOperator::~UnaryOperator()
{}
