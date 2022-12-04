#include "token.hpp"

Token::Token()
  : m_tokentype{}, m_value{}
{}

Token::Token(TokenType t_tokentype)
  : m_tokentype{t_tokentype}, m_value{}
{}

Token::Token(TokenType t_tokentype, int t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{}

Token::Token(TokenType t_tokentype, double t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{}

Token::Token(TokenType t_tokentype, std::string t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{}

auto
Token::type() const -> TokenType
{
  return m_tokentype;
}

auto Token::operator=(Token&& t_token) -> const Token&&
{
  m_tokentype = std::move(t_token.m_tokentype);
  m_value = std::move(t_token.m_value);
}

Token::~Token()
{}
