#include "unary_operator.hpp"

using namespace operators;


UnaryOperator::UnaryOperator(StatementType t_stmnttype, Precedence t_precedence,
                             StatementPointer&& t_stmnt)
  : Expression{t_stmnttype, t_precedence},
    m_first{std::forward<StatementPointer>(t_stmnt)}
{}

auto UnaryOperator::first() -> StatementPointer&
{
  return m_first;
}

UnaryOperator::~UnaryOperator()
{}
