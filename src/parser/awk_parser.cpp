#include "awk_parser.hpp"

#include <memory>
#include <stdexcept>

#include "../debug/log.hpp"
#include "../debug/trace.hpp"

#include "../visitor/print_visitor.hpp"

#include "../enum.hpp"

#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"

#include "../node/list.hpp"
#include "../node/node.hpp"

#include "../node/io/getline.hpp"
#include "../node/io/print.hpp"
#include "../node/io/printf.hpp"
#include "../node/io/redirection.hpp"

#include "../node/rvalue/literal.hpp"
#include "../node/rvalue/rvalue.hpp"

#include "../node/lvalue/array.hpp"
#include "../node/lvalue/field_reference.hpp"
#include "../node/lvalue/variable.hpp"

#include "../node/functions/function.hpp"
#include "../node/functions/function_call.hpp"

#include "../node/operators/arithmetic.hpp"
#include "../node/operators/assignment.hpp"
#include "../node/operators/comparison.hpp"
#include "../node/operators/decrement.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"
#include "../node/operators/string_concatenation.hpp"
#include "../node/operators/unary_prefix.hpp"

// TODO: split the parser and its rules into multiple files, the parser should
// Be able to be done simpler or more properly structured, find a way for this
// To be done properly splitting the parsing rules into multiple classes would
// Be hard to logically justify in a manner that doesnt break logical
// Consistency

// Constructors:
AwkParser::AwkParser(TokenStream t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

// Parsing rule/grammar rules:
auto AwkParser::newline_opt() -> void
{
  TRACE(LogLevel::DEBUG, "NEWLINE OPT");

  while(!eos() && next_if(TokenType::NEWLINE)) {
    TRACE_PRINT(LogLevel::INFO, "Found NEWLINE");
  }
}

auto AwkParser::simple_get() -> NodePtr
{
  using namespace nodes::io;

  TRACE(LogLevel::DEBUG, "SIMPLE GET");
  NodePtr node{nullptr};

  if(next_if(TokenType::GETLINE)) {
    TRACE_PRINT(LogLevel::INFO, "Found GETLINE");
    // TODO: Think about how to implement < redirection
    node = std::make_unique<Getline>(lvalue());
  }

  return node;
}

auto AwkParser::unary_input_function() -> NodePtr
{
  using namespace nodes::io;

  TRACE(LogLevel::DEBUG, "UNARY INPUT FUNCTION");
  NodePtr node{nullptr};

  if(NodePtr lhs{unary_expr()}; lhs) {
    expect(TokenType::PIPE, "|");

    node = std::make_unique<Redirection>(RedirectionOp::PIPE, std::move(lhs),
                                         simple_get());
  }

  return node;
}

// non_unary_input_function : simple_get
//                  | simple_get '<' expr
//                  | non_unary_expr '|' simple_get
//                  ;
auto AwkParser::non_unary_input_function() -> NodePtr
{
  using namespace nodes::io;

  TRACE(LogLevel::DEBUG, "NON UNARY INPUT FUNCTION");
  NodePtr node{nullptr};

  // Recursive causes endless loop
  if(auto lhs{simple_get()}; lhs) {
    if(next_if(TokenType::LESS_THAN)) {
      node = std::make_unique<Redirection>(RedirectionOp::READ, std::move(lhs),
                                           expr());
    } else {
      node = std::move(lhs);
    }
  }
  // TODO: Fix recursion
  //  else if(auto lhs{non_unary_expr()}; lhs) {
  //   expect(TokenType::PIPE, "|");

  //   node = std::make_unique<Redirection>(RedirectionOp::PIPE, std::move(lhs),
  //                                        simple_get());
  // }

  return node;
}

auto AwkParser::lvalue() -> NodePtr
{
  using namespace nodes::lvalue;

  TRACE(LogLevel::DEBUG, "LVALUE");
  NodePtr node{nullptr};

  const auto token{next()};
  switch(token.type()) {
    case TokenType::IDENTIFIER: {
      // We really dont expect these next_tokens to fail
      if(next_if(TokenType::BRACE_OPEN)) {
        TRACE_PRINT(LogLevel::INFO, "Found ARRAY SUBSCRIPT");
        node = std::make_unique<Array>(token.value<std::string>(), expr_list());

        expect(TokenType::BRACE_CLOSE, "]");
      } else {
        TRACE_PRINT(LogLevel::INFO, "Found VARIABLE");
        node = std::make_unique<Variable>(token.value<std::string>());
      }
      break;
    }

    case TokenType::DOLLAR_SIGN: {
      TRACE_PRINT(LogLevel::INFO, "Found FIELD REFERENCE");
      node = std::make_unique<FieldReference>(expr());
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::function() -> NodePtr
{
  using namespace nodes;
  using namespace nodes::functions;

  TRACE(LogLevel::DEBUG, "FUNCTION");
  NodePtr node{nullptr};

  if(next_if(TokenType::FUNCTION)) {
    if(const auto token{get_token()};
       tokentype::is_valid_function_identifier(token.type())) {
      next();

      // TODO: Create a Function class
      expect(TokenType::PAREN_OPEN, "(");
      NodeListPtr params{param_list_opt()};
      expect(TokenType::PAREN_CLOSE, ")");
      newline_opt();
      NodeListPtr action_ptr{static_cast<List*>(action().release())};

      node = std::make_unique<Function>(
        token.value<std::string>(), std::move(params), std::move(action_ptr));
    } else {
      // TODO: Error handling
    }
  }

  return node;
}

// This function parses function calls, it parses builtin functions as well as
// User defined
auto AwkParser::function_call() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "FUNCTION CALL");
  NodePtr node{nullptr};

  switch(next().type()) {
    case TokenType::FUNCTION_IDENTIFIER:
      expect(TokenType::PAREN_OPEN, "(");
      expr_list_opt();
      expect(TokenType::PAREN_CLOSE, ")");
      break;

      // TODO: Add function calls for builtin types

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::ere(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ERE");
  NodePtr node{nullptr};

  // Little helper function to cut down on the bloat
  const auto lambda = [&](ArithmeticOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Arithmetic>(t_op, std::move(t_lhs), std::move(rhs))};
  };

  switch(next().type()) {
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

auto AwkParser::arithmetic(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ARITHMETIC");
  NodePtr node{nullptr};

  // Little helper function to cut down on the bloat
  const auto lambda = [&](ArithmeticOp t_op) -> NodePtr {
    auto ptr{t_rhs()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Arithmetic>(t_op, std::move(t_lhs), std::move(ptr))};
  };

  switch(next().type()) {
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

auto AwkParser::assignment(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ASSIGNMENT");
  NodePtr node{nullptr};

  // TODO: Create an actual function for this that we can call instead of
  // Defining a separate lambda in each function
  const auto lambda = [&](AssignmentOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Assignment>(t_op, std::move(t_lhs), std::move(rhs))};
  };

  switch(next().type()) {
    case TokenType{g_power_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '^='");
      node = lambda(AssignmentOp::POWER);
      break;

    case TokenType{g_multiply_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '*='");
      node = lambda(AssignmentOp::MULTIPLY);
      break;

    case TokenType{g_divide_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '/='");
      node = lambda(AssignmentOp::DIVIDE);
      break;

    case TokenType{g_modulo_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '%='");
      node = lambda(AssignmentOp::MODULO);
      break;

    case TokenType{g_add_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '+='");
      node = lambda(AssignmentOp::ADD);
      break;

    case TokenType{g_subtract_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '-='");
      node = lambda(AssignmentOp::SUBTRACT);
      break;

    case TokenType{g_assignment}:
      TRACE_PRINT(LogLevel::INFO, "Found '='");
      node = lambda(AssignmentOp::REGULAR);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::comparison(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "COMPARISON");
  NodePtr node{nullptr};

  const auto lambda = [&](ComparisonOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression"};

    return std::make_unique<Comparison>(t_op, std::move(t_lhs), std::move(rhs));
  };

  switch(next().type()) {
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

auto AwkParser::logical(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "LOGICAL");
  NodePtr node{nullptr};

  switch(next().type()) {
    case TokenType{g_and}: {
      TRACE_PRINT(LogLevel::INFO, "Found '&&'");
      // Optional newlines are allowed after &&
      newline_opt();
      if(auto rhs{t_rhs()}; rhs) {
        node = std::make_unique<And>(std::move(t_lhs), std::move(rhs));
      } else {
        // TODO: Error handling empty rhs expression is not allowed
      }
      break;
    }

    case TokenType{g_or}: {
      TRACE_PRINT(LogLevel::INFO, "Found '||'");
      // Optional newlines are allowed after ||
      newline_opt();
      if(auto rhs{t_rhs()}; rhs) {
        node = std::make_unique<Or>(std::move(t_lhs), std::move(rhs));
      } else {
        // TODO: Error handling empty rhs expression is not allowed
      }
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

// TODO: Add extra parameter for ternary expression
auto AwkParser::ternary(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
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
auto AwkParser::binary_operator(NodePtr& t_lhs, const ParserFunc& t_rhs)
  -> NodePtr
{
  TRACE(LogLevel::DEBUG, "BINARY OPERATOR");
  NodePtr node{nullptr};

  // TODO: Create lambda for these call chains?
  // Or a macro?
  if(auto ptr{arithmetic(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{comparison(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{logical(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{ternary(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// non_unary_print_expr : '(' expr ')'
//                  | '!' print_expr
//                  | non_unary_print_expr '^'      print_expr
//                  | non_unary_print_expr '*'      print_expr
//                  | non_unary_print_expr '/'      print_expr
//                  | non_unary_print_expr '%'      print_expr
//                  | non_unary_print_expr '+'      print_expr
//                  | non_unary_print_expr '-'      print_expr
//                  | non_unary_print_expr          non_unary_print_expr
//                  | non_unary_print_expr '˜'      print_expr
//                  | non_unary_print_expr NO_MATCH print_expr
//                  | non_unary_print_expr In NAME
//                  | '(' multiple_expr_list ')' In NAME
//                  | non_unary_print_expr AND newline_opt print_expr
//                  | non_unary_print_expr OR  newline_opt print_expr
//                  | non_unary_print_expr '?' print_expr ':' print_expr
//                  | NUMBER
//                  | STRING
//                  | lvalue
//                  | ERE
//                  | lvalue INCR
//                  | lvalue DECR
//                  | INCR lvalue
//                  | DECR lvalue
//                  | lvalue POW_ASSIGN print_expr
//                  | lvalue MOD_ASSIGN print_expr
//                  | lvalue MUL_ASSIGN print_expr
//                  | lvalue DIV_ASSIGN print_expr
//                  | lvalue ADD_ASSIGN print_expr
//                  | lvalue SUB_ASSIGN print_expr
//                  | lvalue '=' print_expr
//                  | FUNC_NAME '(' expr_list_opt ')'
//                      /* no white space allowed before '(' */
//                  | BUILTIN_FUNC_NAME '(' expr_list_opt ')'
//                  | BUILTIN_FUNC_NAME
//                  ;
// FIXME: This is all very similar to non_unary_expr, create a generic helper
// Function that both can use
auto AwkParser::non_unary_print_expr() -> NodePtr
{
  using namespace nodes::operators;
  using namespace nodes::rvalue;

  TRACE(LogLevel::DEBUG, "NON UNARY PRINT EXPR");
  NodePtr node{nullptr};

  bool is_nupe{true};

  // TODO: non_unary_expr and non_unary_print_expr have the exact same part for
  // This
  const auto token{next()};
  switch(token.type()) {
    case TokenType::PAREN_OPEN:
      if(auto ptr{expr()}; ptr) {
        TRACE_PRINT(LogLevel::INFO, "Found (expr)");
        // TODO: Do something
      } else if(auto ptr{multiple_expr_list()}; ptr) {
        expect(TokenType::IN, "in");
        TRACE_PRINT(LogLevel::INFO, "Found MULTIDIMENSIONAL IN");
        // TODO: Do something
      } else {
        // TODO: Error handling
      }

      expect(TokenType::PAREN_CLOSE, ")");
      break;

    case TokenType::NOT:
      TRACE_PRINT(LogLevel::INFO, "Found Not expression");
      node = std::make_unique<Not>(expr());
      break;

    // TODO: Token in the grammar calls for NUMBER? These are not treated
    // differently?
    case TokenType::FLOAT:
      TRACE_PRINT(LogLevel::INFO, "Found FLOAT literal");
      node = std::make_unique<Float>(token.value<double>());
      break;

    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER:
      TRACE_PRINT(LogLevel::INFO, "Found INTEGER literal");
      node = std::make_unique<Integer>(token.value<int>());
      break;

    case TokenType::STRING:
      TRACE_PRINT(LogLevel::INFO, "Found STRING literal");
      node = std::make_unique<String>(token.value<std::string>());
      break;

    case TokenType::INCREMENT: {
      TRACE_PRINT(LogLevel::INFO, "Found --INCREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_unique<Increment>(std::move(ptr), true);
      } else {
        // TODO: Error handling
      }
      break;
    }

    case TokenType::DECREMENT: {
      TRACE_PRINT(LogLevel::INFO, "Found --DECREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_unique<Decrement>(std::move(ptr), true);
      } else {
        // TODO: Error handling
      }
      break;
    }

    default:
      prev();
      is_nupe = false;
      break;
  }

  auto lambda_expr = [&]() {
    return this->print_expr();
  };

  // TOOD: Make this call separate functions
  if(is_nupe) {
    if(auto rhs{non_unary_print_expr()}; rhs) {
      TRACE_PRINT(LogLevel::INFO, "Found STRING CONCAT");
      node =
        std::make_unique<StringConcatenation>(std::move(node), std::move(rhs));
    } else if(auto ptr{arithmetic(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ere(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{logical(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ternary(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    }
  } else {
    // TODO: Analyze the grammar rules to see if this is correct????
    // If 'lvalue <assignmenet> expr' is a valid nue than this should be
    // before The arithmetic, comparison, ere, logical, etc...
    if(auto lhs{lvalue()}; lhs) {
      if(auto ptr{assignment(lhs, lambda_expr)}; ptr) {
        node = std::move(ptr);
        // TODO: Increment, Decrement
      } else if(next_if(TokenType::INCREMENT)) {
        TRACE_PRINT(LogLevel::INFO, "Found INCREMENT++");
        node = std::make_unique<Increment>(std::move(lhs), false);
      } else if(next_if(TokenType::DECREMENT)) {
        TRACE_PRINT(LogLevel::INFO, "Found DECREMENT++");
        node = std::make_unique<Decrement>(std::move(lhs), false);
      } else {
        node = std::move(lhs);
      }
    }
  }

  return node;
}

// unary_print_expr : '+' print_expr
//                  | '-' print_expr
//                  | unary_print_expr '^'      print_expr
//                  | unary_print_expr '*'      print_expr
//                  | unary_print_expr '/'      print_expr
//                  | unary_print_expr '%'      print_expr
//                  | unary_print_expr '+'      print_expr
//                  | unary_print_expr '-'      print_expr
//                  | unary_print_expr          non_unary_print_expr
//                  | unary_print_expr '˜'      print_expr
//                  | unary_print_expr NO_MATCH print_expr
//                  | unary_print_expr In NAME
//                  | unary_print_expr AND newline_opt print_expr
//                  | unary_print_expr OR  newline_opt print_expr
//                  | unary_print_expr '?' print_expr ':' print_expr
//                  ;
// TODO: Unary expr is very similar create a function for both
auto AwkParser::unary_print_expr() -> NodePtr
{
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "UNARY PRINT EXPR");
  NodePtr node{nullptr};

  const auto tokentype{get_token().type()};
  if(tokentype::is_unary_operator(tokentype)) {
    next();
    TRACE_PRINT(LogLevel::INFO, "Found unary operator");

    auto ptr{print_expr()};
    if(!ptr) {
      // TODO: Error handling
      throw std::runtime_error{"Expected print expression"};
    }

    const auto op{unary_prefix::tokentype2enum(tokentype)};
    NodePtr lhs{std::make_unique<UnaryPrefix>(op, std::move(ptr))};

    const auto lambda = [&]() -> NodePtr {
      return this->print_expr();
    };

    if(auto binop_ptr{binary_operator(lhs, lambda)}; binop_ptr) {
      node = std::move(binop_ptr);
    } else {
      node = std::move(lhs);
    }
  } else {
    // unary_input_function is recursive to unary_expr
    // NodePtr lhs{unary_input_function()};
    // node = binary_operator(lhs);
  }

  return node;
}

auto AwkParser::print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PRINT EXPR");
  NodePtr node{nullptr};

  if(auto ptr{unary_print_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_print_expr()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// TODO: multiple_expr_list is very similar create a helper function that both
// Can use
auto AwkParser::print_expr_list() -> NodeListPtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "PRINT EXPR LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  if(auto ptr{print_expr()}; ptr) {
    TRACE_PRINT(LogLevel::INFO, "Found PRINT_EXPR");

    nodes->push_back(std::move(ptr));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      newline_opt();
      if(auto ptr{print_expr()}; ptr) {
        TRACE_PRINT(LogLevel::INFO, "Found ',' PRINT_EXPR");

        nodes->push_back(std::move(ptr));
      } else {
        // TODO: Error handling
      }
    } else {
      break;
    }
  }

  if(!nodes->size()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  // TODO: If we only have one node in the list flatten it to a single NodePtr

  return nodes;
}

auto AwkParser::print_expr_list_opt() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "PRINT EXPR LIST OPT");

  return print_expr_list();
}

// non_unary_expr   : '(' expr ')'
//                  | '!' expr
//                  | non_unary_expr '^'      expr
//                  | non_unary_expr '*'      expr
//                  | non_unary_expr '/'      expr
//                  | non_unary_expr '%'      expr
//                  | non_unary_expr '+'      expr
//                  | non_unary_expr '-'      expr
//                  | non_unary_expr          non_unary_expr
//                  | non_unary_expr '<'      expr
//                  | non_unary_expr LE       expr
//                  | non_unary_expr NE       expr
//                  | non_unary_expr EQ       expr
//                  | non_unary_expr '>'      expr
//                  | non_unary_expr GE       expr
//                  | non_unary_expr '˜'      expr
//                  | non_unary_expr NO_MATCH expr
//                  | non_unary_expr In NAME
//                  | '(' multiple_expr_list ')' In NAME
//                  | non_unary_expr AND newline_opt expr
//                  | non_unary_expr OR  newline_opt expr
//                  | non_unary_expr '?' expr ':' expr
//                  | NUMBER
//                  | STRING
//                  | lvalue
//                  | ERE
//                  | lvalue INCR
//                  | lvalue DECR
//                  | INCR lvalue
//                  | DECR lvalue
//                  | lvalue POW_ASSIGN expr
//                  | lvalue MOD_ASSIGN expr
//                  | lvalue MUL_ASSIGN expr
//                  | lvalue DIV_ASSIGN expr
//                  | lvalue ADD_ASSIGN expr
//                  | lvalue SUB_ASSIGN expr
//                  | lvalue '=' expr
//                  | FUNC_NAME '(' expr_list_opt ')'
//                       /* no white space allowed before '(' */
//                  | BUILTIN_FUNC_NAME '(' expr_list_opt ')'
//                  | BUILTIN_FUNC_NAME
//                  | non_unary_input_function
//                  ;
// TODO: Split these functions
auto AwkParser::non_unary_expr() -> NodePtr
{
  using namespace nodes::operators;
  using namespace nodes::rvalue;

  TRACE(LogLevel::DEBUG, "NON UNARY EXPR");
  NodePtr node{nullptr};

  bool is_nue{true};

  // We still need to do FUNC_NAME and BUILTIN_FUNC_NAME
  const auto token{next()};
  switch(token.type()) {
    case TokenType::PAREN_OPEN:
      if(auto ptr{expr()}; ptr) {
        TRACE_PRINT(LogLevel::INFO, "Found (expr)");
        // TODO: Do something
      } else if(auto ptr{multiple_expr_list()}; ptr) {
        expect(TokenType::IN, "in");
        TRACE_PRINT(LogLevel::INFO, "Found MULTIDIMENSIONAL IN");
        // TODO: Do something
      } else {
        // TODO: Error handling
      }

      expect(TokenType::PAREN_CLOSE, ")");
      break;

    case TokenType::NOT:
      LOG(LogLevel::INFO, "Found Not expression");
      node = std::make_unique<Not>(expr());
      break;

    // TODO: Token in the grammar calls for NUMBER? These are not treated
    // differently?
    case TokenType::FLOAT:
      TRACE_PRINT(LogLevel::INFO, "Found FLOAT literal");
      node = std::make_unique<Float>(token.value<double>());
      break;

    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER:
      TRACE_PRINT(LogLevel::INFO, "Found INTEGER literal");
      node = std::make_unique<Integer>(token.value<int>());
      break;

    case TokenType::STRING:
      TRACE_PRINT(LogLevel::INFO, "Found STRING literal");
      node = std::make_unique<String>(token.value<std::string>());
      break;

    case TokenType::INCREMENT: {
      TRACE_PRINT(LogLevel::INFO, "Found --INCREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_unique<Increment>(std::move(ptr), true);
      } else {
        // TODO: Error handling
      }
      break;
    }

    case TokenType::DECREMENT: {
      TRACE_PRINT(LogLevel::INFO, "Found --DECREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_unique<Decrement>(std::move(ptr), true);
      } else {
        // TODO: Error handling
      }
      break;
    }

    default:
      prev();
      is_nue = false;
      break;
  }

  auto lambda_expr = [&]() {
    return this->expr();
  };

  if(is_nue) {
    if(auto rhs{non_unary_expr()}; rhs) {
      TRACE_PRINT(LogLevel::INFO, "Found STRING CONCAT");
      node =
        std::make_unique<StringConcatenation>(std::move(node), std::move(rhs));
    } else if(auto ptr{arithmetic(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{comparison(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ere(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{logical(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ternary(node, lambda_expr)}; ptr) {
      node = std::move(ptr);
    }
  } else {
    // TODO: Analyze the grammar rules to see if this is correct????
    // If 'lvalue <assignmenet> expr' is a valid nue than this should be
    // before The arithmetic, comparison, ere, logical, etc...
    if(auto lhs{lvalue()}; lhs) {
      if(auto ptr{assignment(lhs, lambda_expr)}; ptr) {
        node = std::move(ptr);
        // TODO: Increment, Decrement
      } else if(next_if(TokenType::INCREMENT)) {
        TRACE_PRINT(LogLevel::INFO, "Found INCREMENT++");
        node = std::make_unique<Increment>(std::move(lhs), false);
      } else if(next_if(TokenType::DECREMENT)) {
        TRACE_PRINT(LogLevel::INFO, "Found DECREMENT++");
        node = std::make_unique<Decrement>(std::move(lhs), false);
      } else {
        node = std::move(lhs);
      }
    } else if(auto ptr{function()}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{non_unary_input_function()}; ptr) {
      node = std::move(ptr);
    }
  }

  return node;
}

// unary_expr       : '+' expr
//                  | '-' expr
//                  | unary_expr '^'      expr
//                  | unary_expr '*'      expr
//                  | unary_expr '/'      expr
//                  | unary_expr '%'      expr
//                  | unary_expr '+'      expr
//                  | unary_expr '-'      expr
//                  | unary_expr          non_unary_expr
//                  | unary_expr '<'      expr
//                  | unary_expr LE       expr
//                  | unary_expr NE       expr
//                  | unary_expr EQ       expr
//                  | unary_expr '>'      expr
//                  | unary_expr GE       expr
//                  | unary_expr '˜'      expr
//                  | unary_expr NO_MATCH expr
//                  | unary_expr In NAME
//                  | unary_expr AND newline_opt expr
//                  | unary_expr OR  newline_opt expr
//                  | unary_expr '?' expr ':' expr
//                  | unary_input_function
//                  ;
auto AwkParser::unary_expr() -> NodePtr
{
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "UNARY EXPR");
  NodePtr node{nullptr};

  const auto tokentype{get_token().type()};
  if(tokentype::is_unary_operator(tokentype)) {
    next();
    TRACE_PRINT(LogLevel::INFO, "Found unary operator");

    auto ptr{expr()};
    if(!ptr) {
      // TODO: Error handling
      throw std::runtime_error{"Expected expression"};
    }

    const auto op{unary_prefix::tokentype2enum(tokentype)};
    NodePtr lhs{std::make_unique<UnaryPrefix>(op, std::move(ptr))};

    const auto lambda = [&]() -> NodePtr {
      return this->expr();
    };

    if(auto binop_ptr{binary_operator(lhs, lambda)}; binop_ptr) {
      node = std::move(binop_ptr);
    } else {
      node = std::move(lhs);
    }
  } else {
    // unary_input_function is recursive to unary_expr
    // NodePtr lhs{unary_input_function()};
    // node = binary_operator(lhs);
  }

  return node;
}

auto AwkParser::expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR");
  NodePtr node{nullptr};

  // TODO: unary_expr() calls expr() which calls unary_expr(), etc etc FIX
  // THIS!
  if(auto ptr{non_unary_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{unary_expr()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}

auto AwkParser::expr_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR OPT");

  return expr();
}

// multiple_expr_list : expr ',' newline_opt expr
//                  | multiple_expr_list ',' newline_opt expr
//                  ;
auto AwkParser::multiple_expr_list() -> NodeListPtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "MULTIPLE EXPR LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  if(auto ptr{expr()}; ptr) {
    TRACE_PRINT(LogLevel::INFO, "Found EXPR");

    nodes->push_back(std::move(ptr));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      newline_opt();
      if(auto ptr{expr()}; ptr) {
        TRACE_PRINT(LogLevel::INFO, "Found ',' EXPR");

        nodes->push_back(std::move(ptr));
      } else {
        // TODO: Error handling
      }
    } else {
      break;
    }
  }

  if(!nodes->size()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  // TODO: If we only have one node in the list flatten it to a single NodePtr

  return nodes;
}

auto AwkParser::expr_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST");
  NodePtr node{nullptr};

  // multiple_expr_list allows one or multiple expr
  if(auto ptr{multiple_expr_list()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}

auto AwkParser::expr_list_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST OPT");

  return expr_list();
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
// TODO: Figure this one out
auto AwkParser::output_redirection() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "OUTPUT REDIRECTION");
  NodePtr node{nullptr};

  const auto token{next()};

  switch(token.type()) {
    case TokenType::TRUNC:
      break;

    case TokenType::APPEND:
      break;

    case TokenType::PIPE:
      break;

    default:
      prev();
      break;
  }

  // TODO: Pass this expr expression to the upper expressions
  expr();

  return node;
}

// TODO: Refactor!
auto AwkParser::simple_print_statement() -> NodePtr
{
  using namespace nodes::io;

  TRACE(LogLevel::DEBUG, "SIMPLE PRINT STATEMENT");
  NodePtr node{nullptr};

  // Convenience lambda
  const auto lambda = [&]() -> NodeListPtr {
    NodeListPtr node{nullptr};

    if(next_if(TokenType::PAREN_OPEN)) {
      node = multiple_expr_list();
      expect(TokenType::PAREN_CLOSE, ")");
    } else {
      node = print_expr_list_opt();
    }

    return node;
  };

  if(next_if(TokenType::PRINT)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'print'");

    node = std::make_unique<Print>(lambda());
  } else if(next_if(TokenType::PRINTF)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'printf");

    node = std::make_unique<Printf>(lambda());
  }

  return node;
}

auto AwkParser::print_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PRINT STATEMENT");
  NodePtr node{nullptr};

  if(auto ptr{simple_print_statement()}; ptr) {
    // TODO: Implement output redirection for print statements
    node = std::move(ptr);
    if(auto redirection_ptr{output_redirection()}; redirection_ptr) {
      // TODO: Think this one out, possibly return multiple return values?
    }
  }

  return node;
}

// TODO: Do list rule
// simple_statement : Delete NAME '[' expr_list ']'
auto AwkParser::simple_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE STATEMENT");
  NodePtr node{nullptr};

  if(next_if(TokenType::DELETE)) {
    expect(TokenType::IDENTIFIER, "Name");
    expect(TokenType::BRACE_OPEN, "[");
    expr_list();
    expect(TokenType::BRACE_CLOSE, "]");

    // TODO: Return Delete statement
  } else if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{print_statement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto AwkParser::simple_statement_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE STATEMENT OPT");

  return simple_statement();
}

// TODO: Return these keyword objects
// terminatable_statement : simple_statement
//                  | Break
//                  | Continue
//                  | Next
//                  | Exit expr_opt
//                  | Return expr_opt
//                  | Do newline_opt terminated_statement While '(' expr ')'
//                  ;
auto AwkParser::terminatable_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "TERMINATABLE STATEMENT");
  NodePtr node{nullptr};

  bool is_keyword{true};
  const auto keyword{next()};
  switch(keyword.type()) {
    case TokenType::BREAK:
      break;

    case TokenType::CONTINUE:
      break;

    case TokenType::NEXT:
      break;

    case TokenType::EXIT:
      expr_opt();
      break;

    case TokenType::RETURN:
      expr_opt();
      break;

    case TokenType::DO:
      newline_opt();
      terminated_statement();
      expect(TokenType::WHILE, "while");
      expect(TokenType::PAREN_OPEN, "(");
      expr();
      expect(TokenType::PAREN_CLOSE, ")");
      break;

    default:
      is_keyword = false;
      prev();
      break;
  }

  if(!is_keyword) {
    node = simple_statement();
  }

  return node;
}

// unterminated_statement : terminatable_statement
//                  | If '(' expr ')' newline_opt unterminated_statement
//                  | If '(' expr ')' newline_opt terminated_statement
//                       Else newline_opt unterminated_statement
//                  | While '(' expr ')' newline_opt unterminated_statement
//                  | For '(' simple_statement_opt ';'
//                   expr_opt ';' simple_statement_opt ')' newline_opt
//                       unterminated_statement
//                  | For '(' NAME In NAME ')' newline_opt
//                       unterminated_statement
//                  ;
auto AwkParser::unterminated_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNTERMINATED STATEMENT");
  NodePtr node{nullptr};

  if(auto ptr{expr_opt()}; ptr) {
    node = std::move(ptr);
  } else {
    const auto token{next()};
    switch(token.type()) {
      case TokenType::IF:
        break;

      case TokenType::WHILE:
        break;

      case TokenType::FOR:
        break;

      default:
        prev();
        break;
    }
  }

  return node;
}

// terminated_statement : action newline_opt
//                  | If '(' expr ')' newline_opt terminated_statement
//                  | If '(' expr ')' newline_opt terminated_statement
//                        Else newline_opt terminated_statement
//                  | While '(' expr ')' newline_opt terminated_statement
//                  | For '(' simple_statement_opt ';'
//                       expr_opt ';' simple_statement_opt ')' newline_opt
//                       terminated_statement
//                  | For '(' NAME In NAME ')' newline_opt
//                       terminated_statement
//                  | ';' newline_opt
//                  | terminatable_statement NEWLINE newline_opt
//                  | terminatable_statement ';'     newline_opt
//                  ;
auto AwkParser::terminated_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "TERMINATED STATEMENT");
  NodePtr node{nullptr};

  // TODO: Handle each one of these clauses in separate functions
  switch(next().type()) {
    case TokenType::IF: {
      expect(TokenType::PAREN_OPEN, "(");
      expr();
      expect(TokenType::PAREN_CLOSE, ")");

      newline_opt();
      terminated_statement();

      if(next_if(TokenType::ELSE)) {
        newline_opt();
        terminated_statement();

        // TODO: Create Else node
      } else {
        // TODO: Create If node
      }
      break;
    }

    case TokenType::WHILE: {
      expect(TokenType::PAREN_OPEN, "(");
      expr();
      expect(TokenType::PAREN_CLOSE, ")");
      newline_opt();
      terminated_statement();
      break;
    }

    case TokenType::FOR: {
      expect(TokenType::PAREN_OPEN, "(");

      // TODO: Do rest
      break;
    }

    case TokenType::SEMICOLON: {
      TRACE_PRINT(LogLevel::INFO, "Found ';");
      newline_opt();
      break;
    }

    default: {
      prev();

      if(auto ptr{terminatable_statement()}; ptr) {
        node = std::move(ptr);

        if(const auto tokentype{get_token().type()};
           tokentype::is_terminator(tokentype)) {
          next();
          TRACE_PRINT(LogLevel::INFO, "Found ",
                      (tokentype == TokenType::SEMICOLON) ? "';'" : "NEWLINE");
        } else {
          throw std::runtime_error{"Expected a TERMINATOR"};
        }

        newline_opt();
        break;
      }
    }
  }

  return node;
}

// This rule is made to match atleast one unterminated statement
// Unterminated statements end on a -> '\n'
auto AwkParser::unterminated_statement_list() -> NodePtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "UNTERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    if(auto ptr{unterminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  if(!nodes->size()) {
    throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  return nodes;
}

// This rule is made to match atleast one terminated statement
// Terminated statements end on a -> ';'
auto AwkParser::terminated_statement_list() -> NodePtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "TERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    if(auto ptr{terminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  if(!nodes->size()) {
    throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  // Create a NodeListPtr from the NodePtrList
  return nodes;
}

// terminator       : terminator NEWLINE
//                  |            ';'
//                  |            NEWLINE
//                  ;
auto AwkParser::terminator() -> void
{
  TRACE(LogLevel::DEBUG, "TERMINATOR IS NOT TESTED WARNING!!!!!");
  TRACE(LogLevel::DEBUG, "TERMINATOR");

  const auto token{next()};
  // TODO: Improve
  if(!tokentype::is_terminator(token.type()))
    std::runtime_error{"Expected a terminator!!!"};

  newline_opt();
}

// action           : '{' newline_opt                             '}'
//                  | '{' newline_opt terminated_statement_list   '}'
//                  | '{' newline_opt unterminated_statement_list '}'
//                  ;
auto AwkParser::action() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ACTION");
  NodePtr node{nullptr};

  if(next_if(TokenType::ACCOLADE_OPEN)) {
    TRACE_PRINT(LogLevel::INFO, "Found '{'");

    newline_opt();

    if(auto ptr{terminated_statement_list()}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{unterminated_statement_list()}; ptr) {
      node = std::move(ptr);
    }

    expect(TokenType::ACCOLADE_CLOSE, "}");
    TRACE_PRINT(LogLevel::INFO, "Found '}'");
  }

  return node;
}

// special_pattern  : Begin
//                  | End
//                  ;
auto AwkParser::special_pattern() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SPECIAL PATTERN");
  NodePtr node{nullptr};

  if(next_if(TokenType::BEGIN)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'BEGIN'");

  } else if(next_if(TokenType::END)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'END'");
  }

  return node;
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto AwkParser::normal_pattern() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NORMAL PATTERN");
  NodePtr node{nullptr};

  if(auto ptr{expr()}; ptr) {
    const auto token{next()};
    if(token.type() == TokenType::COMMA) {
      newline_opt();
      expr();

      // TODO: We must create a NodelistPtr to combine both expr
    } else {
      prev();
      node = std::move(ptr);
    }
  }

  return node;
}

auto AwkParser::pattern() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PATTERN");
  NodePtr node{nullptr};

  if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{special_pattern()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto AwkParser::param_list() -> NodeListPtr
{
  using namespace nodes;
  using namespace nodes::lvalue;

  TRACE(LogLevel::DEBUG, "PARAM LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  if(const auto token{next()}; token.type() == TokenType::IDENTIFIER) {
    TRACE_PRINT(LogLevel::INFO, "Found NAME");

    nodes->push_back(std::make_unique<Variable>(token.value<std::string>()));
  } else {
    prev();
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      TRACE_PRINT(LogLevel::INFO, "Found ',' NAME");
      const auto token{expect(TokenType::IDENTIFIER, "NAME")};

      nodes->push_back(std::make_unique<Variable>(token.value<std::string>()));
    } else {
      break;
    }
  }

  if(!nodes->size()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  return nodes;
}

auto AwkParser::param_list_opt() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "PARAM LIST OPT");

  return param_list();
}

// item also covers what is the valid toplevel syntax:
// item             : action
//                  | pattern action
//                  | normal_pattern
//                  | Function NAME      '(' param_list_opt ')'
//                        newline_opt action
//                  | Function FUNC_NAME '(' param_list_opt ')'
//                        newline_opt action
//                  ;
auto AwkParser::item() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ITEM");
  NodePtr node{nullptr};

  if(auto ptr{action()}; ptr) {
    node = std::move(ptr);
  } else if(auto pattern_ptr{pattern()}; pattern_ptr) {
    if(auto action_ptr{action()}; action_ptr) {
      // TODO: Figure out
    } else {
      // TODO: Properly throw later
      throw std::runtime_error{"Expected Expression"};
    }

    // Resolve this?
    // How should we represent this in AST?
  } else if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  } else if(true) {
    // TODO: Implement function parsing for now ignore?
  }

  // TODO: This is just for debugging the parser
  if(node) {
    std::cout << "Printing AST\n";
    PrintVisitor visitor;
    node->accept(&visitor);
  }

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto AwkParser::item_list() -> NodeListPtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "ITEM LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    if(auto ptr{item()}; ptr) {
      nodes->push_back(std::move(ptr));
      terminator();
    } else {
      break;
    }
  }

return nodes;
}

// program          : item_list
//                  | item_list item
//                  ;
auto AwkParser::program() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PROGRAM");
  NodePtr node{nullptr};

  // TODO Piece these together some way into an AST structure
  if(auto list_ptr{item_list()}; list_ptr) {
  } else if(auto item_ptr{item()}; item_ptr) {
    // item() is optional
  } else {
    // TODO: Error handling
    std::cout << "No items in program" << std::endl;
  }

  return node;
}

auto AwkParser::parse() -> Ast
{
  LOG_PRINTLN("=== PARSING ===");

  Ast ast;
  program();

  LOG_PRINTLN();

  return ast;
}

// Destructors:
AwkParser::~AwkParser()
{}
