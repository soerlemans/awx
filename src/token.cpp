#include "token.hpp"

Token::Token(TokenType t_tokentype, int t_value)
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

Token::~Token()
{}
