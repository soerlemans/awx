#include "token.hpp"


using namespace token;

Token::Token(TokenType t_type, const FilePosition& t_file_pos)
  : m_type{t_type}, m_file_pos{t_file_pos}
{}

Token::Token(TokenType t_type, TokenValue t_value,
             const FilePosition& t_file_pos)
  : m_type{t_type}, m_value{t_value}, m_file_pos{t_file_pos}
{}

auto Token::type() const -> TokenType
{
  return m_type;
}

auto Token::value() const -> TokenValue
{
  return m_value;
}

auto Token::file_position() const -> const FilePosition&
{
  return m_file_pos;
}
