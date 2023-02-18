#include "token.hpp"

#include <string_view>

#include "../enum.hpp"


Token::Token(TokenType t_type, const FilePosition& t_file_pos)
  : m_type{t_type}, m_file_pos{t_file_pos}
{}

auto Token::type() const -> TokenType
{
  return m_type;
}

auto Token::file_position() const -> const FilePosition&
{
  return m_file_pos;
}

auto Token::print() const -> void
{
  std::cout << "Token - Type: " << enum2underlying_type(this->type());

  print_if<int>("Int");
  print_if<double>("Double");
  print_if<std::string>("String");
}
