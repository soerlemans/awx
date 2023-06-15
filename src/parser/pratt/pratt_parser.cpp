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
using namespace node::rvalue;

// Methods:
PrattParser::PrattParser(token::TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

auto PrattParser::non_unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");
  NodePtr lhs;

  // Literals
  switch(const auto token{next()}; token.type()) {
    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER: {
      DBG_TRACE_PRINT(INFO, "Found INTEGER literal: ");
      lhs = std::make_shared<Integer>(token.value<int>());
      break;
    }

    default:
      prev();
      break;
  }

  // while(true) {
  // }

  return lhs;
}

auto PrattParser::unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY PRINT EXPR");
  NodePtr lhs;

  // Unary expressions:
  switch(const auto tokentype{next().type()}; tokentype) {
    case TokenType::PLUS:
      [[fallthrough]];
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

    // FIXME: filter using switch
    if(!m_infix.count(token.type())) {
      break;
    }

    const auto [lbp, rbp] = m_infix.at(token.type());
    if(lbp < t_min_bp) {
      prev();
      break;
    }

    // FIXME: Segfaults, rhs nullptr?
    NodePtr rhs = unary_print_expr(rbp);
    if(rhs) {
      lhs = std::make_shared<Arithmetic>(ArithmeticOp::ADD, std::move(lhs),
                                         std::move(rhs));
    }
  }

  return lhs;
}

auto PrattParser::print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "PRINT EXPR");
  NodePtr node;

  if(auto ptr{unary_print_expr(t_min_bp)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_print_expr(t_min_bp)}; ptr) {
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
