#include "expression.hpp"


Expression::Expression(StatementType t_stmnttype, Precedence t_precedence)
  :Statement{t_stmnttype}, m_precedence{t_precedence}
{}

auto Expression::precedence() -> Precedence
{
  return m_precedence;
}

Expression::~Expression()
{}
