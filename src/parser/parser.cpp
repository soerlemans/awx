#include "parser.hpp"

#include "../lexer/token_type.hpp"


Parser::Parser(TokenStream t_token_stream)
  : m_token_stream{t_token_stream}, m_toplevel{false}
{}

auto Parser::identifier(const Token& t_token) -> bool
{}

// Handle keyword related tokens
// Return a bool if it is a keyword
auto Parser::keyword(const Token& t_token) -> bool
{
  using namespace reserved::keywords;

  bool is_keyword{true};
  switch(t_token.type())
    {
      case g_function.tokentype():
        break;

      case g_return.tokentype():
        break;

      case g_if.tokentype():
        break;

      case g_do.tokentype():
        break;

      case g_while.tokentype():
        break;

      case g_for.tokentype():
        break;

      default:
        is_keyword = false;
        break;
    }

  return is_keyword;
}

auto Parser::string(const Token& t_token) -> bool
{
  bool is_string{false};

  return is_string;
}

auto Parser::symbol(const Token& t_token) -> bool
{
  bool is_symbol{false};

  return is_symbol;
}

// Parse toplevel forms
auto Parser::toplevel() -> bool
{
  bool is_toplevel{true};
  const TokenType token_type{m_token_stream.token().type()};

  switch(token_type)
    {
      case TokenType::FUNCTION:
        break;

      case TokenType::IDENTIFIER:
        break;

      default:
        is_toplevel = false;
        break;
    }

  return is_toplevel;
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  // Ast ast;
  for(; m_token_stream.eos(); m_token_stream.next())
    if(toplevel())

  // return ast;
	  return {};
}

Parser::~Parser()
{}
