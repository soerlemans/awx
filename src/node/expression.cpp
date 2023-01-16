#include "expression.hpp"

using namespace nodes;


Expression::Expression(Precedence t_precedence)
  : Node{NodeType::EXPRESSION}, m_precedence{t_precedence}
{}

auto Expression::precedence() -> Precedence
{
  return m_precedence;
}

Expression::~Expression()
{}
