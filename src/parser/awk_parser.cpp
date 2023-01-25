#include "awk_parser.hpp"

#include <memory>
#include <stdexcept>

#include "../debug/log.hpp"
#include "../debug/trace.hpp"
#include "../enum.hpp"

#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"

#include "../node/io/getline.hpp"
#include "../node/io/pipe.hpp"
#include "../node/io/print.hpp"
#include "../node/io/printf.hpp"

#include "../node/rvalue/literal.hpp"
#include "../node/rvalue/rvalue.hpp"

#include "../node/lvalue/array.hpp"
#include "../node/lvalue/field_reference.hpp"
#include "../node/lvalue/variable.hpp"

#include "../node/operators/arithmetic.hpp"
#include "../node/operators/assignment.hpp"
#include "../node/operators/comparison.hpp"
#include "../node/operators/decrement.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"
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
    TRACE_PRINT(LogLevel::DEBUG, "Found NEWLINE");
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

    node = std::make_unique<Pipe>(std::move(lhs), simple_get());
  }

  return node;
}

// non_unary_input_function : simple_get
//                  | simple_get '<' expr
//                  | non_unary_expr '|' simple_get
//                  ;
auto AwkParser::non_unary_input_function() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NON UNARY INPUT FUNCTION");
  NodePtr node{nullptr};

  // Recursive causes endless loop
  if(auto ptr{simple_get()}; ptr) {
    // TODO: Implement output redirection
    node = std::move(ptr);

    if(next_if(TokenType::LESS_THAN)) {
      // This is recursive causes endless loop expr();
      expr();
    }
  }
  // else
  //  if(auto ptr{non_unary_expr()}; ptr) {
  //  }

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
        // What do with expr_list???
        // TODO: Include expr_list somehow sometime
        expr_list();
        expect(TokenType::BRACE_CLOSE, "]");

        TRACE_PRINT(LogLevel::INFO, "Found Array subscript");
        node = std::make_unique<Array>(token.value<std::string>());
      } else {
        TRACE_PRINT(LogLevel::INFO, "Found VARIABLE");
        node = std::make_unique<Variable>(token.value<std::string>());
      }
      break;
    }

    case TokenType::DOLLAR_SIGN: {
      TRACE_PRINT(LogLevel::INFO, "Found Field reference");
      node = std::make_unique<FieldReference>(expr());
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::string_concatenation(NodePtr& t_lhs, const ParserFunc& t_rhs)
  -> NodePtr
{
  TRACE(LogLevel::DEBUG, "STRING CONCAT");
  NodePtr node{nullptr};

  // TODO: Create StringConcat class
  // t_rhs();

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
    auto ptr{t_rhs()};
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

auto AwkParser::assignment(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "ASSIGNMENT");
  NodePtr node{nullptr};

  // TODO: Create an actual function for this that we can call instead of
  // Defining a separate lambda in each function
  const auto lambda = [&](AssignmentOp t_op) -> NodePtr {
    auto ptr{t_rhs()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return NodePtr{
      std::make_unique<Assignment>(t_op, std::move(t_lhs), std::move(ptr))};
  };

  const auto op{next().type()};
  switch(op) {
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
    auto ptr{t_rhs()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression"};

    return std::make_unique<Comparison>(t_op, std::move(t_lhs), std::move(ptr));
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

auto AwkParser::logical(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  using namespace reserved::symbols;
  using namespace nodes::operators;

  TRACE(LogLevel::DEBUG, "LOGICAL");
  NodePtr node{nullptr};

  const auto lambda = [&]<typename T>() -> NodePtr {
    NodePtr rhs{nullptr};

    // Optional newlines are allowed after && and ||
    newline_opt();
    if(auto ptr{t_rhs()}; ptr) {
      rhs = std::move(ptr);
    } else {
      // TODO: Error handling empty rhs expression is not allowed
    }

    if(!rhs) {
      throw std::runtime_error{"Expected Expression"};
    }

    return std::make_unique<T>(std::move(t_lhs), std::move(rhs));
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
auto AwkParser::non_unary_print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NON UNARY PRINT EXPR");
  NodePtr node{nullptr};

  if(next_if(TokenType::PAREN_OPEN)) {
    if(auto ptr{expr()}; ptr) {
      // TODO: Grouping?
      node = std::move(ptr);
    } else if(auto ptr{multiple_expr_list()}; ptr) {
      expect(TokenType::IN, "In");
      expect(TokenType::IDENTIFIER, "Identifier");

      // TODO: Grouping?
      node = std::move(ptr);
    }
  } else if(next_if(TokenType::NOT)) {
    print_expr();
  } else {
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
auto AwkParser::unary_print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNARY PRINT EXPR");
  NodePtr node{nullptr};

  const auto prefix{next()};
  if(tokentype::is_unary_operator(prefix.type())) {
    auto lhs{print_expr()};

    const auto lambda = [&]() -> NodePtr {
      return this->print_expr();
    };

    if(auto ptr{arithmetic(lhs, lambda)}; ptr) {
      // TODO: Implement
      // } else if(auto ptr{arithmetic(lhs)}; ptr) {
    }
  }

  return node;
}

// print_expr       : unary_print_expr
//                  | non_unary_print_expr
//                  ;
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

// print_expr_list  : print_expr
//                  | print_expr_list ',' newline_opt print_expr
//                  ;
auto AwkParser::print_expr_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PRINT EXPR LIST");
  NodePtr node{nullptr};

  if(auto ptr{print_expr()}; ptr) {
    if(next_if(TokenType::COMMA)) {
      // TODO: Set expr
      newline_opt();
      print_expr();
    } else {
      // Create print_expr node??
    }
  }

  return node;
}

// print_expr_list_opt : /* empty */
//                  | print_expr_list
//                  ;
auto AwkParser::print_expr_list_opt() -> NodePtr
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

  const auto token{next()};

  bool is_nue{true};
  // We still need to fix ERE, NUMBER? FUNC_NAME and BUILTIN_FUNC_NAME
  switch(token.type()) {
    case TokenType::PAREN_OPEN:
      if(auto ptr{expr()}; ptr) {
        // TODO: Do something
      } else if(auto ptr{multiple_expr_list()}; ptr) {
        expect(TokenType::IN, "in");
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
      TRACE_PRINT(LogLevel::DEBUG, "Found FLOAT literal");
      node = std::make_unique<Float>(token.value<double>());
      break;

    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER:
      TRACE_PRINT(LogLevel::DEBUG, "Found INTEGER literal");
      node = std::make_unique<Integer>(token.value<int>());
      break;

    case TokenType::STRING:
      TRACE_PRINT(LogLevel::DEBUG, "Found STRING literal");
      node = std::make_unique<String>(token.value<std::string>());
      break;

    // TOOD: ERE?
    case TokenType::INCREMENT:
      LOG(LogLevel::INFO, "Found prefix Increment");
      node = std::make_unique<Increment>(lvalue(), true);
      break;

    case TokenType::DECREMENT:
      LOG(LogLevel::INFO, "Found prefix Decrement");
      node = std::make_unique<Decrement>(lvalue(), true);
      break;

    default:
      prev();
      is_nue = false;
      break;
  }

  auto lambda_expr = [&]() {
    return this->expr();
  };

  if(is_nue) {

    auto lambda_nue = [&]() {
      return this->non_unary_expr();
    };

    if(auto ptr{arithmetic(node, lambda_expr)}; ptr) {
      node = std::move(ptr);

      // Note: String concatenation accepts lambda_nue
    } else if(auto ptr{string_concatenation(node, lambda_nue)}; ptr) {
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
    // If 'lvalue <assignmenet> expr' is a valid nue than this should be before
    // The arithmetic, comparison, ere, logical, etc...
    if(auto ptr{lvalue()}; ptr) {
      if(auto assign_ptr{assignment(ptr, lambda_expr)}; assign_ptr) {
        node = std::move(assign_ptr);
        // TODO: Increment, Decrement
        // } else if(auto ptr) {
      }
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

    auto expr_ptr{expr()};
    if(!expr_ptr) {
      // TODO: Error handling
      throw std::runtime_error{"Expected expression"};
    }

    NodePtr lhs{nullptr};

    const auto op{unary_prefix::tokentype2enum(tokentype)};
    lhs = std::make_unique<UnaryPrefix>(op, std::move(expr_ptr));

    const auto lambda = [&]() -> NodePtr {
      return this->expr();
    };

    node = binary_operator(lhs, lambda);
  } else {
    // unary_input_function is recursive to unary_expr
    // NodePtr lhs{unary_input_function()};
    // node = binary_operator(lhs);
  }

  return node;
}

// expr             : unary_expr
//                  | non_unary_expr
//                  ;
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

// expr_opt         : /* empty */
//                  | expr
//                  ;
auto AwkParser::expr_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR OPT");
  NodePtr node{nullptr};

  if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// multiple_expr_list : expr ',' newline_opt expr
//                  | multiple_expr_list ',' newline_opt expr
//                  ;
auto AwkParser::multiple_expr_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "MULTIPLE EXPR LIST");
  NodePtr node{nullptr};


  return node;
}

// expr_list        : expr
//                  | multiple_expr_list
//                  ;
auto AwkParser::expr_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST");
  NodePtr node{nullptr};

  if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{multiple_expr_list()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}

// expr_list_opt    : /* empty */
//                  | expr_list
//                  ;
auto AwkParser::expr_list_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST OPT");
  NodePtr node{expr_list()};

  return node;
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
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

// simple_print_statement : Print  print_expr_list_opt
//                  | Print  '(' multiple_expr_list ')'
//                  | Printf print_expr_list
//                  | Printf '(' multiple_expr_list ')'
//                  ;
// TODO: Refactor!
auto AwkParser::simple_print_statement() -> NodePtr
{
  using namespace nodes::io;

  TRACE(LogLevel::DEBUG, "SIMPLE PRINT STATEMENT");
  NodePtr node{nullptr};

  // Convenience lambda
  const auto lambda = [&]() -> NodePtr {
    NodePtr node{nullptr};

    if(next_if(TokenType::PAREN_OPEN)) {
      node = multiple_expr_list();
      expect(TokenType::PAREN_CLOSE, ")");
    } else {
      node = print_expr_list_opt();
    }

    return node;
  };

  if(next_if(TokenType::PRINT)) {
    TRACE_PRINT(LogLevel::DEBUG, "Found 'print'");

    node = std::make_unique<Print>(lambda());
  } else if(next_if(TokenType::PRINTF)) {
    TRACE_PRINT(LogLevel::DEBUG, "Found 'printf");

    node = std::make_unique<Printf>(lambda());
  }

  return node;
}

// print_statement  : simple_print_statement
//                  | simple_print_statement output_redirection
//                  ;
auto AwkParser::print_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PRINT STATEMENT");
  NodePtr node{nullptr};

  if(auto ptr{simple_print_statement()}; ptr) {
    // TODO: Implement output redirection for print statements
    node = std::move(ptr);
    if(auto redirection_ptr{output_redirection()}; redirection_ptr) {
    }
  }

  return node;
}

// simple_statement : Delete NAME '[' expr_list ']'
//                  | expr
//                  | print_statement
//                  ;
auto AwkParser::simple_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE STATEMENT");
  NodePtr node{nullptr};

  if(next_if(TokenType::DELETE)) {
    expect(TokenType::IDENTIFIER, "Name");
    expect(TokenType::BRACE_OPEN, "[");
    expr_list();
    expect(TokenType::BRACE_CLOSE, "]");
  } else if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{print_statement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// simple_statement_opt : /* empty */
//                  | simple_statement
//                  ;
auto AwkParser::simple_statement_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE STATEMENT OPT");

  return simple_statement();
}

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
    }

    case TokenType::WHILE: {
      expect(TokenType::PAREN_OPEN, "(");
      expr();
      expect(TokenType::PAREN_CLOSE, ")");
      newline_opt();
      terminated_statement();
    }

    case TokenType::FOR:
      expect(TokenType::PAREN_OPEN, "(");

      // TODO: Do rest
      break;

    case TokenType::SEMICOLON:
      TRACE_PRINT(LogLevel::DEBUG, "Found ';");
      newline_opt();
      break;

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
// Unterminated statements end on a -> \n
// unterminated_statement_list : unterminated_statement
//                  | terminated_statement_list unterminated_statement
//                  ;
auto AwkParser::unterminated_statement_list() -> NodePtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "UNTERMINATED STATEMENT LIST");
  NodeListPtr node{nullptr};

  if(auto ptr{unterminated_statement()}; ptr) {
    node = std::make_unique<List>();
    node->push_back(std::move(ptr));

    while(!eos()) {
      if(auto ptr{unterminated_statement()}; ptr) {
        node->push_back(std::move(ptr));
      } else {
        break;
      }
    }
  } else {
    // TODO: Error handling
    // EXCPECTED ATLEAST ONE...
  }

  return NodePtr{node.release()};
}

// This rule is made to match atleast one terminated statement
// Terminated statements end on a -> ;
// terminated_statement_list : terminated_statement
//                  | terminated_statement_list terminated_statement
//                  ;
auto AwkParser::terminated_statement_list() -> NodePtr
{
  using namespace nodes;

  TRACE(LogLevel::DEBUG, "TERMINATED STATEMENT LIST");
  NodeListPtr node{nullptr};

  if(auto ptr{terminated_statement()}; ptr) {
    node = std::make_unique<List>();
    node->push_back(std::move(ptr));

    while(!eos()) {
      if(auto ptr{terminated_statement()}; ptr) {
        node->push_back(std::move(ptr));
      } else {
        break;
      }
    }
  } else {
    // TODO: Error handling
    // EXCPECTED ATLEAST ONE...
  }

  // Create a NodeListPtr from the NodePtrList
  return NodePtr{node.release()};
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
      // DO SOMETHING!
      // TODO: We dont reach here cause of some reason??????
    } else if(auto ptr{unterminated_statement_list()}; ptr) {
      // DO SOMETHING!
    } else {
      // TODO:: Error handling
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
    } else {
      prev();
    }
  }

  return node;
}

// pattern          : normal_pattern
//                  | special_pattern
//                  ;
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

// param_list       : NAME_ptr
//                  | param_list ',' NAME_ptr
//                  ;
auto AwkParser::param_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PARAM LIST");
  NodePtr node{nullptr};

  // const auto token{next()};

  return node;
}

// param_list_opt   : /* empty */
//                  | param_list
//                  ;
auto AwkParser::param_list_opt() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PARAM LIST OPT");
  NodePtr node{nullptr};

  if(auto ptr{param_list()}; ptr) {
    node = std::move(ptr);
  }

  return node;
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
    auto action_ptr{action()};

    if(!action_ptr) {
      // TODO: Properly throw later
      throw std::runtime_error{"Expected Expression"};
    }

    // Resolve this?
    // How should we represent this in AST?
  } else if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  } else if(true) {
    // TODO: Implement function parsing for now ignore?
  }

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto AwkParser::item_list() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ITEM LIST");
  NodePtr node{nullptr};

  do {
    node = item();

    if(node) {
      terminator();
    }
  } while(node);

  return node;
}

// program          : item_list
//                  | item_list item
//                  ;
auto AwkParser::program() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PROGRAM");
  NodePtr node{nullptr};

  // TODO Piece these together some way into an AST structure
  node = item_list();

  if(auto item_ptr{item()}; item_ptr) {
    // item() is optional
  }

  return node;
}

auto AwkParser::parse() -> Ast
{
  LOG_PRINT("=== PARSING ===");

  Ast ast;
  program();

  LOG_PRINT();
  return ast;
}

// Destructors:
AwkParser::~AwkParser()
{}
