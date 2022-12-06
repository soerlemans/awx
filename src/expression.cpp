#include <type_traits>
#include <utility>

#include "expression.hpp"


Expression::Expression(TokenType t_tokentype)
  :m_tokentype{t_tokentype}
{}

template<ExpressionChild T>
Expression::Expression(TokenType t_tokentype, T&& t_expr)
  :m_tokentype{t_tokentype}, m_left{std::make_unique<T>(t_expr)}
{}

Expression::Expression(Token t_token)
  :m_tokentype{t_token.type()}
{}

auto Expression::tokentype() -> TokenType
{
  return m_tokentype;
}

auto Expression::left() -> Expression&
{
  return *m_left;
}

// auto Expression::left(Expression& t_expr) -> void
// {
//   m_left.
// }

Expression::~Expression()
{}
