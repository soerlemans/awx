#include "unary_operator.hpp"

#include <utility>


UnaryOperator::UnaryOperator(StatementType t_stmnttype, Precedence t_precedence,
                             StatementPointer&& t_stmnt)
  : Expression{t_stmnttype, t_precedence},
    m_left{std::forward<StatementPointer>(t_stmnt)}
{}

auto UnaryOperator::left() -> StatementPointer&
{
  return m_left;
}

UnaryOperator::~UnaryOperator()
{}
