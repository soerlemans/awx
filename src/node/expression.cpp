#include "expression.hpp"

using namespace node;

using namespace visitor;


Expression::Expression(Precedence t_precedence): m_precedence{t_precedence}
{}

auto Expression::precedence() -> Precedence
{
  return m_precedence;
}
