#include "parser.hpp"

#include "../lexer/token_type.hpp"


Parser::Parser(TokenStream t_tokenstream)
  :m_tokenstream{t_tokenstream}
{}

auto Parser::identifier(const Token& t_token) -> void
{
}

auto Parser::keyword(const Token& t_token) -> void
{
  using namespace reserved::keywords;

  // TODO: Create different functions that construct an expression and return it
  switch(t_token.type())
	{
	case g_function.tokentype():
	  break;

	case g_return.tokentype():
	  break;

	case g_if.tokentype():
	  break;

	case g_else.tokentype():
	  break;

	case g_do.tokentype():
	  break;

	case g_while.tokentype():
	  break;

	case g_for.tokentype():
	  break;

	case g_in.tokentype():
	  break;

	default:
	  break;
	}
}

auto Parser::numeric(const Token& t_token) -> void
{
  switch(t_token.type())
	{
	default:
	  break;
	}
}

auto Parser::string(const Token& t_token) -> void
{
  switch(t_token.type())
	{
	default:
	  break;
	}
}

auto Parser::symbol(const Token& t_token) -> void
{
  switch(t_token.type())
	{
	default:
	  break;
	}
}

auto Parser::parse() -> Ast
{
  using namespace reserved;
  for(const auto& token : m_tokenstream)
	{
	  
	}

  return {};
}

Parser::~Parser()
{}
