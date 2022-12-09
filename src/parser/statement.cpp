#include <cassert>
#include <type_traits>
#include <utility>

#include "statement.hpp"


Statement::Statement(ExpressionType t_expressiontype)
  :m_expressiontype{t_expressiontype}
{}

auto Statement::type() -> StatementType
{
  return m_statementtype;
}

Statement::~Statement()
{}
