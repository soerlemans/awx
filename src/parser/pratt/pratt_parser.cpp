#include "pratt_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Includes:
#include "../../debug/log.hpp"
#include "../../debug/trace.hpp"
#include "../../node/include.hpp"


// Using statements:
using namespace parser::pratt;

using namespace token;

using namespace node;
using namespace node::operators;

// Methods:
PrattParser::PrattParser(token::TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

auto PrattParser::non_unary_print_expr() -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");
  NodePtr node;

  while(true) {
  }

  return node;
}

auto PrattParser::unary_print_expr(const int t_min_bp) -> NodePtr
{

  DBG_TRACE(VERBOSE, "UNARY PRINT EXPR");
  NodePtr lhs;

  // Unary expressions:
  switch(const auto tokentype{next().type()}; tokentype) {
    case TokenType::PLUS:
    case TokenType::MINUS: {
      DBG_TRACE(VERBOSE, "Found UNARY PREFIX");

      const auto [lbp, rbp] = m_prefix.at(tokentype);
      lhs = std::make_shared<UnaryPrefix>(tokentype, print_expr(rbp));
      break;
    }

    default:
      prev();
      break;
  }

  // Binary expressions:
  while(true) {
    const auto token{next()};

    const auto [lbp, rbp] = m_infix.at(token.type());
    if(lbp < t_min_bp) {
      break;
    }

    next();
    NodePtr lhs = std::make_shared<Arithmetic>(
      ArithmeticOp::ADD, std::move(lhs), unary_print_expr(rbp));
  }

  return lhs;
}

auto PrattParser::print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "PRINT EXPR");
  NodePtr node;

  if(auto ptr{unary_print_expr(t_min_bp)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_print_expr()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto PrattParser::non_unary_expr() -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY EXPR");
  NodePtr node, nue;

  return node;
}

auto PrattParser::unary_expr() -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY EXPR");
  NodePtr node;

  return node;
}

auto PrattParser::expr() -> NodePtr
{
  DBG_TRACE(VERBOSE, "EXPR");
  NodePtr node;

  if(auto ptr{unary_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_expr()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}
