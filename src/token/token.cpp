#include "token.hpp"

#include <iostream>

#include "../enum.hpp"


Token::Token(TokenType t_type, FilePosition t_file_pos)
  : m_type{t_type}, m_value{}, m_file_pos{t_file_pos}
{}

auto Token::type() const -> TokenType
{
  return m_type;
}

auto Token::file_position() -> FilePosition
{
  return m_file_pos;
}

auto Token::print() -> void
{
  std::cout << "Token - Type: " << enum2underlying_type(this->type());

  // TODO: Macro this away?
  if(const auto verify{this->check<int>()}; verify)
    std::cout << " Int: " << *verify << '\n';
  else if(const auto verify{this->check<double>()}; verify)
    std::cout << " Double: " << *verify << '\n';
  else if(const auto verify{this->check<std::string>()}; verify)
    std::cout << " String: " << *verify << '\n';
  else
    ; // TODO: Error handling
}
