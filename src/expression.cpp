#include <cassert>
#include <type_traits>
#include <utility>

#include "expression.hpp"


Expression::Expression(ExpressionType t_expressiontype)
  :m_expressiontype{t_expressiontype}
{}

auto Expression::type() -> ExpressionType
{
  return m_expressiontype;
}

Expression::~Expression()
{}
