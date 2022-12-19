#include "parser.hpp"

#include "../lexer/token_type.hpp"


Parser::Parser(TokenStream t_tokenstream)
  :m_tokenstream{t_tokenstream}
{}

auto Parser::identifier(const Token& t_token) -> void
{
}

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

	case g_else.tokentype():
	  break;

	case g_do.tokentype():
	  break;

	case g_while.tokentype():
	  break;

	case g_for.tokentype():
	  break;

	// TODO: Handle in identifier case
	// case g_in.tokentype():
	//   break;

	default:
	  is_keyword = false;
	  break;
	}

  return is_keyword;
}

auto Parser::numeric(const Token& t_token) -> bool
{
  bool is_numeric{true};
  switch(t_token.type())
	{
	case TokenType::INTEGER:
	  break;

	case TokenType::HEX:
	  break;

	case TokenType::FLOAT:
	  break;


	default:
	  is_numeric = false;
	  break;
	}

  return is_numeric;
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

auto Parser::parse() -> Ast
{
  using namespace reserved;

  Ast ast;

  for(const auto& token : m_tokenstream)
	{
	}

  return ast;
}

Parser::~Parser()
{}
