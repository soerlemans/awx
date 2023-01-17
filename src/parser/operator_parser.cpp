#include "operator_parser.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "../debug/log.hpp"
#include "../debug/trace.hpp"

#include "../node/operators/arithmetic.hpp"
#include "../node/operators/comparison.hpp"
#include "../node/operators/logical.hpp"


// Constructor:
OperatorParser::OperatorParser(TokenStream t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

// Methods:
auto OperatorParser::string_concatenation(NodePtr& t_lhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ARITHMETIC");
  NodePtr node{nullptr};

  return node;
}

auto OperatorParser::ere(NodePtr& t_lhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ARITHMETIC");
  NodePtr node{nullptr};

  // Little helper function to cut down on the bloat
  auto lambda = [&](ArithmeticOp t_op) -> NodePtr {
    auto ptr{expr()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Arithmetic>(t_op, std::move(t_lhs), std::move(ptr))};
  };

  const auto op{next().type()};
  switch(op) {
    case TokenType{g_ere_match}:
      TRACE_PRINT(LogLevel::INFO, "Found '~'");
      // TODO: Figure out if ere should have its own class or not?
      // Probably should have its own class
      // node = lambda(ComparisonOp::SUBTRACT);
      break;

    case TokenType{g_ere_no_match}:
      TRACE_PRINT(LogLevel::INFO, "Found '!~'");
      // node = lambda(ComparisonOp::SUBTRACT);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto OperatorParser::arithmetic(NodePtr& t_lhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ARITHMETIC");
  NodePtr node{nullptr};

  // Little helper function to cut down on the bloat
  auto lambda = [&](ArithmeticOp t_op) -> NodePtr {
    auto ptr{expr()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Arithmetic>(t_op, std::move(t_lhs), std::move(ptr))};
  };

  const auto op{next().type()};
  switch(op) {
    case TokenType{g_caret}:
      TRACE_PRINT(LogLevel::INFO, "Found '^'");
      node = lambda(ArithmeticOp::POWER);
      break;

    case TokenType{g_asterisk}:
      TRACE_PRINT(LogLevel::INFO, "Found '*'");
      node = lambda(ArithmeticOp::MULTIPLY);
      break;

    case TokenType{g_slash}:
      TRACE_PRINT(LogLevel::INFO, "Found '/'");
      node = lambda(ArithmeticOp::DIVIDE);
      break;

    case TokenType{g_percent_sign}:
      TRACE_PRINT(LogLevel::INFO, "Found '%'");
      node = lambda(ArithmeticOp::MODULO);
      break;

    case TokenType{g_plus}:
      TRACE_PRINT(LogLevel::INFO, "Found '+'");
      node = lambda(ArithmeticOp::ADD);
      break;

    case TokenType{g_minus}:
      TRACE_PRINT(LogLevel::INFO, "Found '-'");
      node = lambda(ArithmeticOp::SUBTRACT);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto OperatorParser::comparison(NodePtr& t_lhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "COMPARISON");
  NodePtr node{nullptr};

  auto lambda = [&](ComparisonOp t_op) -> NodePtr {
    auto ptr{expr()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Comparison>(t_op, std::move(t_lhs), std::move(ptr))};
  };

  const auto op{next().type()};
  switch(op) {
    case TokenType{g_less_than}:
      TRACE_PRINT(LogLevel::INFO, "Found '<'");
      node = lambda(ComparisonOp::LESS_THAN);
      break;

    case TokenType{g_less_than_equal}:
      TRACE_PRINT(LogLevel::INFO, "Found '<='");
      node = lambda(ComparisonOp::LESS_THAN_EQUAL);
      break;

    case TokenType{g_equal}:
      TRACE_PRINT(LogLevel::INFO, "Found '=='");
      node = lambda(ComparisonOp::EQUAL);
      break;

    case TokenType{g_not_equal}:
      TRACE_PRINT(LogLevel::INFO, "Found '!='");
      node = lambda(ComparisonOp::NOT_EQUAL);
      break;

    case TokenType{g_greater_than}:
      TRACE_PRINT(LogLevel::INFO, "Found '>'");
      node = lambda(ComparisonOp::GREATER_THAN);
      break;

    case TokenType{g_greater_than_equal}:
      TRACE_PRINT(LogLevel::INFO, "Found '>='");
      node = lambda(ComparisonOp::GREATER_THAN_EQUAL);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto OperatorParser::logical(NodePtr& t_lhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "LOGICAL");
  NodePtr node{nullptr};

  auto lambda = [&]<typename T>() -> NodePtr {
    NodePtr rhs{nullptr};

    // Optional newlines are allowed after && and ||
    newline_opt();
    if(auto ptr{expr()}; ptr) {
      rhs = std::move(ptr);
    }

    if(!rhs) {
      throw std::runtime_error{"Expected Expression"};
    }

    return NodePtr{std::make_unique<T>(std::move(t_lhs), std::move(rhs))};
  };

  const auto op{next().type()};
  switch(op) {
    case TokenType{g_and}:
      TRACE_PRINT(LogLevel::INFO, "Found '&&'");
      // Invalid syntax?
      // node = lambda<And>();
      break;

    case TokenType{g_or}:
      TRACE_PRINT(LogLevel::INFO, "Found '||'");
      // Invalid syntax?
      // node = lambda<Or>();
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto OperatorParser::ternary(NodePtr& t_lhs) -> NodePtr
{
  using namespace reserved::symbols;

  TRACE(LogLevel::DEBUG, "TERNARY");
  NodePtr node{nullptr};

  if(next_if(TokenType{g_questionmark})) {
    // TODO: Handle Ternary expression
  }

  return node;
}

// TODO: Not a grammar rule function, but a function intended for parsing
// binary Operator statements
auto OperatorParser::binary_operator(NodePtr& t_lhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "BINARY OPERATOR");
  NodePtr node{nullptr};

  // TODO: Create lambda for these call chains?
  // Or a macro?
  if(auto ptr{arithmetic(t_lhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{comparison(t_lhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{logical(t_lhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{ternary(t_lhs)}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Destructor:
OperatorParser::~OperatorParser()
{}

