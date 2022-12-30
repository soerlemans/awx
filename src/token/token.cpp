#include "token.hpp"

#include <iostream>

#include "../enum.hpp"


Token::Token(TokenType t_tokentype): m_tokentype{t_tokentype}, m_value{}
{
}

Token::Token(TokenType t_tokentype, int t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{
}

Token::Token(TokenType t_tokentype, double t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{
}

Token::Token(TokenType t_tokentype, std::string t_value)
  : m_tokentype{t_tokentype}, m_value{t_value}
{
}

auto Token::type() const -> TokenType
{
  return m_tokentype;
}

Token::~Token()
{
}

// Exported functions:
auto print_token(const Token& t_token) -> void
{
  std::cout << "Token - Type: " << enum2underlying_type(t_token.type());

  // TODO: Macro this away?
  if(const auto verify{t_token.check<int>()}; verify)
    std::cout << " Int: " << *verify << '\n';
  else if(const auto verify{t_token.check<double>()}; verify)
    std::cout << " Double: " << *verify << '\n';
  else if(const auto verify{t_token.check<std::string>()}; verify)
    std::cout << " String: " << *verify << '\n';
  else
    ; // TODO: Error handling
}
