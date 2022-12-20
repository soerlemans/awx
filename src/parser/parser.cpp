#include "parser.hpp"

#include "../lexer/token_type.hpp"


Parser::Parser(TokenStream t_token_stream)
  : m_token_stream{t_token_stream}
{}

auto Parser::function() -> NodePointer
{
  // TODO: Define Function node for this
}

// Check for valid toplevel form tokens
auto Parser::toplevel() -> NodePointer
{
  NodePointer node;
  const TokenType token_type{m_token_stream.token().type()};

  // TODO: Create seperate functions for handling/defining the next tokens
  switch(token_type)
    {
      case TokenType::FUNCTION:
        function();
        break;

      case TokenType::REGEX:
        // Handle regex pattern
        break;

      case TokenType::IDENTIFIER:
      case TokenType::INTEGER:
      case TokenType::HEX:
      case TokenType::FLOAT:
        // Handle conditional
        break;

		// Field reference does not have its own unique token
      case TokenType::DOLLAR_SIGN:
        // handle field reference
        break;

      default:
		// Error handling
        break;
    }

  return node;
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  Ast ast;
  for(; m_token_stream.eos(); m_token_stream.next())
	{
	  // Ast is pieced together from calling nested functions
	  // That each return a Node
	  ast.add(toplevel());
	}

  // return ast;
  return {};
}

Parser::~Parser()
{}
