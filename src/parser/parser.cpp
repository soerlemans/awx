#include "parser.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// TODO: place better!:
// Static functions:
namespace {
// Fetch the tokens you need to see if it is a conditional
auto condition_tokens(TokenStream& t_token_stream) -> std::tuple<Token, Token>
{
  const Token op{t_token_stream.next()};

  // Incomplete conditional expression
  if(t_token_stream.eos())
    throw std::runtime_error{"Incomplete conditional expression!"};

  const Token rhs{t_token_stream.token()};

  return {op, rhs};
}
} // namespace


// Class definitions:
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

// TODO: Think of a better place for these
namespace {
// Processes logical junctions like && (conjunction) and || (disjunction)
auto logical_junction(const Token& t_lhs, const Token& t_op, const Token& t_rhs)
  -> NodePointer
{
  NodePointer node{nullptr};

  switch(t_op.type())
    {
      case TokenType::AND:
        std::cout << "AND\n";
        break;

      case TokenType::OR:
        std::cout << "OR\n";
        break;

      default:
        break;
    }

  return node;
}

auto comparison(const Token& t_lhs, const Token& t_op, const Token& t_rhs)
  -> NodePointer
{
  NodePointer node{nullptr};
  switch(t_op.type())
    {
      case TokenType::LESS_THAN:
        std::cout << "LESS_THAN\n";
        break;

      case TokenType::LESS_THAN_EQUAL:
        std::cout << "LESS_THAN_EQUAL\n";
        break;

      case TokenType::EQUAL:
        std::cout << "EQUAL\n";
        break;

      case TokenType::NOT_EQUAL:
        std::cout << "EQUAL\n";
        break;

      case TokenType::GREATER_THAN:
        std::cout << "GREATER_THAN\n";
        break;

      case TokenType::GREATER_THAN_EQUAL:
        std::cout << "GREATER_THAN_EQUAL\n";
        break;

      default:
        break;
    }

  return node;
}
} // namespace

auto Parser::condition() -> NodePointer
{
  NodePointer node{nullptr};

  // Conditionals require lookahead
  const Token lhs{m_token_stream.next()};
  const auto [op, rhs] = condition_tokens(m_token_stream);

  if(tokentype::is_logical_junction(op.type()))
    logical_junction(lhs, op, rhs);
  else if(tokentype::is_comparison_operator(op.type()))
    comparison(lhs, op, rhs);
  else
    {
      // If we dont find a valid operator comparison operator just set
      // m_token_stream back to its initial state
      m_token_stream.prev(2);

      // If we dont detect a logical junction or comparison operator it can
      // still be a valid conditional if the variable or expression can be
      // converted to a boolean
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
