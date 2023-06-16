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

// TODO: Have this also handle multidimensional 'in' statements?
// TODO: Create a function that extracts expressions from in between '(', ')'
auto PrattParser::grouping() -> NodePtr
{
  DBG_TRACE(VERBOSE, "GROUPING");
  NodePtr node;

  if(next_if(TokenType::PAREN_OPEN)) {
    DBG_TRACE_PRINT(VERBOSE, "Found GROUPING");

    node = std::make_shared<Grouping>(expr());
    expect(TokenType::PAREN_CLOSE, ")");
  }

  return node;
}

// negation == not, !
auto PrattParser::negation(const ParserFunc& t_expr) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NEGATION");
  NodePtr node;

  if(next_if(TokenType::NOT)) {
    DBG_TRACE_PRINT(INFO, "Found NOT");
    if(NodePtr expr_ptr{t_expr()}; expr_ptr) {
      node = std::make_shared<Not>(std::move(expr_ptr));
    } else {
      // TODO: Error handling
    }
  }

  return node;
}

// TODO: Implement match
// This method parses literals
auto PrattParser::literal() -> NodePtr
{
  DBG_TRACE(VERBOSE, "LITERAL");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    // TODO: Token in the grammar calls for NUMBER? These are not treated
    // differently?
    case TokenType::FLOAT:
      DBG_TRACE_PRINT(INFO, "Found FLOAT literal");
      node = std::make_shared<Float>(token.value<double>());
      break;

    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER:
      DBG_TRACE_PRINT(INFO, "Found INTEGER literal: ");
      node = std::make_shared<Integer>(token.value<int>());
      break;

    case TokenType::STRING:
      DBG_TRACE_PRINT(INFO,
                      "Found STRING literal: ", token.value<std::string>());
      node = std::make_shared<String>(token.value<std::string>());
      break;

    // TODO: match
    case TokenType::REGEX:
      DBG_TRACE_PRINT(INFO,
                      "Found REGEX literal: ", token.value<std::string>());
      node = std::make_shared<Regex>(token.value<std::string>());
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::non_unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");
  NodePtr lhs;

  // Literals
  if(auto ptr{literal()}; ptr) {
    lhs = std::move(ptr);
  } else {
    switch(const auto tokentype{next().type()}; tokentype) {
      case TokenType::NOT: {
        DBG_TRACE(VERBOSE, "Found NOT");

        const auto [lbp, rbp] = m_prefix.at(tokentype);
        lhs = std::make_shared<UnaryPrefix>(tokentype, print_expr(rbp));
        break;
      }

      default:
        prev();
        break;
    }
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
  while(!eos()) {
    const auto token{next()};

    // FIXME: filter using switch, this is temporary code
    if(!m_infix.count(token.type())) {
      prev();
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
