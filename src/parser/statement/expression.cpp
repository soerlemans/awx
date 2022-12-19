#include "expression.hpp"


Expression::Expression(Precedence t_precedence)
  :Statement{StatementType::EXPRESSION}, m_precedence{t_precedence}
{}

auto Expression::precedence() -> Precedence
{
  return m_precedence;
}

Expression::~Expression()
{}
