#include "binaryexpression.hpp"

#include <utility>

BinaryExpression::BinaryExpression(ExpressionType t_exprtype,
                                   Expression&& t_left, Expression&& t_right)
  : UnaryExpression{t_exprtype, std::forward<Expression>(t_left)},
    m_right{std::make_unique<Expression>(t_right)}
{}

auto BinaryExpression::right() const -> Expression
{
  return *m_right;
}

BinaryExpression::~BinaryExpression()
{}
