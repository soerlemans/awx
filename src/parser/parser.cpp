#include "parser.hpp"

#include <iostream>
#include <stdexcept>

#include "../exception/syntax_error.hpp"
#include "../token/token_type.hpp"


Parser::Parser(TokenStream t_token_stream): m_token_stream{t_token_stream}
{}

auto Parser::function() -> NodePointer
{
  // TODO: Define Function node for this
  NodePointer node{nullptr};

  return node;
}

auto Parser::identifier() -> NodePointer
{
  NodePointer node{nullptr};

  return node;
}

auto Parser::literal() -> NodePointer
{
  NodePointer node{nullptr};
  const TokenType token_type{m_token_stream.token().type()};


  return node;
}
auto Parser::condition() -> NodePointer
{
  NodePointer node{nullptr};
  const TokenType token_type{m_token_stream.token().type()};

  switch(token_type)
    {
      case TokenType::AND:
      case TokenType::OR:

      case TokenType::EQUAL:
      case TokenType::NOT_EQUAL:
        break;
    }

  return node;
}

auto Parser::body() -> NodePointer
{
  NodePointer node{nullptr};
  const TokenType token_type{m_token_stream.token().type()};


  return node;
}

// Check for valid toplevel form tokens
auto Parser::toplevel() -> NodePointer
{
  NodePointer node{nullptr};
  const TokenType token_type{m_token_stream.token().type()};

  // TODO: Remove when done with parsing
  print_token(m_token_stream.token());

  // TODO: Create seperate functions for handling/defining the next tokens
  switch(token_type)
    {
      case TokenType::FUNCTION:
        function();
        break;

      case TokenType::IDENTIFIER:
      case TokenType::DOLLAR_SIGN:
        // TODO: Regex might require additional processing rules
      case TokenType::REGEX:
      case TokenType::INTEGER:
      case TokenType::HEX:
      case TokenType::FLOAT:
        condition();
        break;

      case TokenType::ACCOLADE_OPEN:
        // call function for body processing
        break;

      default:
        // FIXME: Have tokens know their line, column, filepath, etc...
        throw std::runtime_error{"Invalid toplevel token"};
        break;
    }

  return node;
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  Ast ast;
  for(; !m_token_stream.eos(); m_token_stream.next())
    {
      // Ast is pieced together from calling nested functions
      // That each return a NodePointer to eachother
      ast.add(toplevel());
    }

  return ast;
}

Parser::~Parser()
{}
