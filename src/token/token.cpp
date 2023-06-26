#include "token.hpp"


using namespace token;
using namespace container;

Token::Token(const TokenType t_type, const TextPosition& t_pos)
  : m_type{t_type}, m_pos{t_pos}
{}

Token::Token(const TokenType t_type, const TokenValue t_value,
             const TextPosition& t_pos)
  : m_type{t_type}, m_value{t_value}, m_pos{t_pos}
{}

auto Token::type() const -> TokenType
{
  return m_type;
}

auto Token::value() const -> TokenValue
{
  return m_value;
}

auto Token::position() const -> const TextPosition&
{
  return m_pos;
}
