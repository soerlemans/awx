#include "unaryexpression.hpp"

#include "expression.hpp"


UnaryExpression::UnaryExpression(ExpressionType t_exprtype, Expression&& t_expr)
  :Expression{t_exprtype}, m_left{std::make_unique<Expression>(t_expr)}
{}

auto UnaryExpression::left() const -> Expression
{
  return *m_left;
}

UnaryExpression::~UnaryExpression()
{}
