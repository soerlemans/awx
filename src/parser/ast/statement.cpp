#include <cassert>
#include <type_traits>
#include <utility>

#include "statement.hpp"


Statement::Statement(StatementType t_stmnttype)
  :m_stmnttype{t_stmnttype}
{}

auto Statement::type() -> StatementType
{
  return m_stmnttype;
}

Statement::~Statement()
{}
