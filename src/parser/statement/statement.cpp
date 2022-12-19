#include <cassert>
#include <type_traits>
#include <utility>

#include "statement.hpp"


Statement::Statement(StatementType t_statementtype)
  :m_statementtype{t_statementtype}
{}

auto Statement::type() -> StatementType
{
  return m_statementtype;
}

Statement::~Statement()
{}
