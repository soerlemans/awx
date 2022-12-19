#include "token.hpp"


Token::Token(TokenType t_token_type)
  : m_token_type{t_token_type}, m_value{}
{}

Token::Token(TokenType t_token_type, int t_value)
  : m_token_type{t_token_type}, m_value{t_value}
{}

Token::Token(TokenType t_token_type, double t_value)
  : m_token_type{t_token_type}, m_value{t_value}
{}

Token::Token(TokenType t_token_type, std::string t_value)
  : m_token_type{t_token_type}, m_value{t_value}
{}

auto
Token::type() const -> TokenType
{
  return m_token_type;
}

Token::~Token()
{}
