#include "awk_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Includes:
#include "../debug/log.hpp"
#include "../debug/trace.hpp"
#include "../enum.hpp"
#include "../node/include.hpp"
#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// Using statements:
using namespace reserved::symbols;

using namespace nodes;
using namespace nodes::control;
using namespace nodes::functions;
using namespace nodes::io;
using namespace nodes::lvalue;
using namespace nodes::operators;
using namespace nodes::recipes;
using namespace nodes::rvalue;

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
  TRACE(LogLevel::DEBUG, "SIMPLE GET");
  NodePtr node;

  if(next_if(TokenType::GETLINE)) {
    TRACE_PRINT(LogLevel::INFO, "Found GETLINE");

    node = std::make_unique<Getline>(lvalue());
  }

  return node;
}

auto AwkParser::unary_input_function() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNARY INPUT FUNCTION");
  NodePtr node;

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
  TRACE(LogLevel::DEBUG, "NON UNARY INPUT FUNCTION");
  NodePtr node;

  // Recursive causes endless loop
  if(auto lhs{simple_get()}; lhs) {
    if(next_if(TokenType::LESS_THAN)) {
      node = std::make_unique<Redirection>(RedirectionOp::READ, std::move(lhs),
                                           expr());
    } else {
      node = std::move(lhs);
    }
    // TODO: Fix recursion
  }
  // else if(auto lhs{non_unary_expr()}; lhs) {
  //   expect(TokenType::PIPE, "|");

  //   node = std::make_unique<Redirection>(RedirectionOp::PIPE, std::move(lhs),
  //                                        simple_get());
  // }

  return node;
}

auto AwkParser::lvalue() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "LVALUE");
  NodePtr node;

  const auto token{next()};
  switch(token.type()) {
    case TokenType::IDENTIFIER: {
      const auto name{token.value<std::string>()};
      // We really dont expect these next_tokens to fail
      if(next_if(TokenType::BRACE_OPEN)) {
        TRACE_PRINT(LogLevel::INFO, "Found ARRAY SUBSCRIPT");
        node = std::make_unique<Array>(name, expr_list());

        expect(TokenType::BRACE_CLOSE, "]");
      } else {
        TRACE_PRINT(LogLevel::INFO, "Found VARIABLE", name);
        node = std::make_unique<Variable>(name);
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
  TRACE(LogLevel::DEBUG, "FUNCTION");
  NodePtr node;

  if(next_if(TokenType::FUNCTION)) {
    TRACE_PRINT(LogLevel::DEBUG, "Found FUNCTION");

    if(const auto token{get_token()};
       tokentype::is_valid_function_identifier(token.type())) {
      next();
      const auto name{token.value<std::string>()};
      TRACE_PRINT(LogLevel::DEBUG, "Valid FUNCTION IDENTIFIER: ", name);

      // TODO: Create a Function class
      expect(TokenType::PAREN_OPEN, "(");
      NodeListPtr params{param_list_opt()};
      expect(TokenType::PAREN_CLOSE, ")");

      newline_opt();
      NodeListPtr body{static_cast<List*>(action().release())};

      TRACE_PRINT(LogLevel::INFO, "Found a FUNCTION");

      node =
        std::make_unique<Function>(name, std::move(params), std::move(body));
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
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    case TokenType::BUILTIN_FUNCTION:
      [[fallthrough]];
    case TokenType::FUNCTION_IDENTIFIER: {
      expect(TokenType::PAREN_OPEN, "(");
      NodeListPtr args{expr_list_opt()};
      expect(TokenType::PAREN_CLOSE, ")");

      auto name{token.value<std::string>()};
      TRACE_PRINT(LogLevel::INFO, "Found a FUNCTION CALL: ", name);

      node = std::make_unique<FunctionCall>(std::move(name), std::move(args));
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::match(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "MATCH");
  NodePtr node;

  // Little helper function to cut down on the bloat
  const auto lambda{[&](MatchOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression after (NO)MATCH"};

    return NodePtr{
      std::make_unique<Match>(t_op, std::move(t_lhs), std::move(rhs))};
  }};

  switch(next().type()) {
    case TokenType{g_ere_match}:
      TRACE_PRINT(LogLevel::INFO, "Found '~'");
      node = lambda(MatchOp::MATCH);
      break;

    case TokenType{g_ere_no_match}:
      TRACE_PRINT(LogLevel::INFO, "Found '!~'");
      node = lambda(MatchOp::NO_MATCH);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::arithmetic(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ARITHMETIC");
  NodePtr node;

  // Little helper function to cut down on the bloat
  const auto lambda = [&](ArithmeticOp t_op) -> NodePtr {
    auto ptr{t_rhs()};
    if(!ptr)
      throw std::runtime_error{"Expected Expression after ARITHMETIC"};

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
  TRACE(LogLevel::DEBUG, "ASSIGNMENT");
  NodePtr node;

  // TODO: Create an actual function for this that we can call instead of
  // Defining a separate lambda in each function
  const auto lambda = [&](AssignmentOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression after ASSIGNMENT"};

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
  TRACE(LogLevel::DEBUG, "COMPARISON");
  NodePtr node;

  const auto lambda = [&](ComparisonOp t_op) -> NodePtr {
    auto rhs{t_rhs()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression after COMPARISON"};

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

auto AwkParser::membership(NodePtr& t_lhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "MEMBERSHIP");
  NodePtr node;

  if(next_if(TokenType::IN)) {
    TRACE_PRINT(LogLevel::DEBUG, "Found MEMBERSHIP");
    const auto name{expect(TokenType::IDENTIFIER, "NAME")};
    node =
      std::make_unique<Membership>(std::move(t_lhs), name.value<std::string>());
  }

  return node;
}

auto AwkParser::logical(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "LOGICAL");
  NodePtr node;

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
  TRACE(LogLevel::DEBUG, "TERNARY");
  NodePtr node;

  // FIXME: simple_print_statement has a rule that conflicts and does not make
  // It possible to detect if it is a print() or print () ? : ;
  if(next_if(TokenType{g_questionmark})) {
    TRACE(LogLevel::DEBUG, "Found TERNARY");
    NodePtr then_ptr{t_rhs()};
    if(!then_ptr) {
      // TODO: Error handling
    }

    expect(TokenType::COLON, ":");
    NodePtr else_ptr{t_rhs()};
    if(!else_ptr) {
      // TODO: Error handling
    }

    node = std::make_unique<Ternary>(std::move(t_lhs), std::move(then_ptr),
                                     std::move(else_ptr));
  }

  return node;
}

// Expressions that are the same across non unary print expr and unary print
// expr
auto AwkParser::universal_print_expr(NodePtr& t_lhs, const ParserFunc& t_rhs)
  -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNIVERSAL PRINT EXPR");
  NodePtr node;

  // if(auto rhs{non_unary_expr()}; rhs) {
  //   TRACE_PRINT(LogLevel::INFO, "Found STRING CONCAT");
  //   node =
  //     std::make_unique<StringConcatenation>(std::move(node), std::move(rhs));
  // } else

  if(auto ptr{arithmetic(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{match(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{membership(t_lhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{logical(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{ternary(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Expressions that are the same across non unary expr and unary expr
auto AwkParser::universal_expr(NodePtr& t_lhs, const ParserFunc& t_rhs)
  -> NodePtr
{
  NodePtr node;

  if(auto ptr{universal_print_expr(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{comparison(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// TODO: Have this also handle multidimensional 'in' statements?
// TODO: Create a function that extracts expressions from in between '(', ')'
auto AwkParser::grouping() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "GROUPING");
  NodePtr node;

  if(next_if(TokenType::PAREN_OPEN)) {
    TRACE_PRINT(LogLevel::DEBUG, "Found GROUPING");

    node = std::make_unique<Grouping>(expr());
    expect(TokenType::PAREN_CLOSE, ")");
  }

  return node;
}

// negation == not, !
auto AwkParser::negation(const ParserFunc& t_expr) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NEGATION");
  NodePtr node;

  if(next_if(TokenType::NOT)) {
    TRACE_PRINT(LogLevel::INFO, "Found NOT");
    if(NodePtr expr_ptr{t_expr()}; expr_ptr) {
      node = std::make_unique<Not>(std::move(expr_ptr));
    } else {
      // TODO: Error handling
    }
  }

  return node;
}

// TODO: Implement match
// This method parses literals
auto AwkParser::literal() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "LITERAL");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    // TODO: Token in the grammar calls for NUMBER? These are not treated
    // differently?
    case TokenType::FLOAT:
      TRACE_PRINT(LogLevel::INFO, "Found FLOAT literal");
      node = std::make_unique<Float>(token.value<double>());
      break;

    case TokenType::HEX:
      [[fallthrough]];
    case TokenType::INTEGER:
      TRACE_PRINT(LogLevel::INFO, "Found INTEGER literal: ");
      node = std::make_unique<Integer>(token.value<int>());
      break;

    case TokenType::STRING:
      TRACE_PRINT(LogLevel::INFO,
                  "Found STRING literal: ", token.value<std::string>());
      node = std::make_unique<String>(token.value<std::string>());
      break;

    // TODO: match
    case TokenType::REGEX:
      TRACE_PRINT(LogLevel::INFO,
                  "Found REGEX literal: ", token.value<std::string>());
      node = std::make_unique<Regex>(token.value<std::string>());
      break;

    default:
      prev();
      break;
  }

  return node;
}

// Prefix operator parses prefix increment and decrement
auto AwkParser::prefix_operator() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PREFIX OPERATOR");
  NodePtr node;

  // TODO: Find a way to shorten or macro this?
  switch(next().type()) {
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
      break;
  }

  return node;
}

// Parses lvalue statements that are the same in non unary expr and unary expr
auto AwkParser::universal_lvalue(NodePtr& t_lhs, const ParserFunc& t_rhs)
  -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNIVERSAL LVALUE");
  NodePtr node;

  if(auto ptr{assignment(t_lhs, t_rhs)}; ptr) {
    node = std::move(ptr);
  } else {
    switch(next().type()) {
      case TokenType::INCREMENT:
        TRACE_PRINT(LogLevel::INFO, "Found INCREMENT++");
        node = std::make_unique<Increment>(std::move(t_lhs), false);
        break;

      case TokenType::DECREMENT:
        TRACE_PRINT(LogLevel::INFO, "Found DECREMENT--");
        node = std::make_unique<Decrement>(std::move(t_lhs), false);
        break;

      default:
        prev();
        break;
    }
  }

  return node;
}

// Parses unary prefixes like having a + or - before an expression
auto AwkParser::unary_prefix(const ParserFunc& t_rhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNARY PREFIX");
  NodePtr node;

  switch(const auto tokentype{next().type()}; tokentype) {
    case TokenType::PLUS:
    case TokenType::MINUS: {
      TRACE(LogLevel::DEBUG, "Found UNARY PREFIX");

      NodePtr rhs{t_rhs()};
      if(!rhs) {
        throw std::runtime_error{"Expected an expression after + or -"};
      }

      node = std::make_unique<UnaryPrefix>(tokentype, std::move(rhs));
      break;
    }
    default:
      prev();
      break;
  }

  return node;
}

// TODO: Split FOR and WHILE into their own functions
auto AwkParser::loop(const ParserFunc& t_body) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "LOOP");
  NodePtr node;

  // TODO: Split even further?
  switch(next().type()) {
    case TokenType::WHILE: {
      TRACE_PRINT(LogLevel::INFO, "Found WHILE");

      expect(TokenType::PAREN_OPEN, "(");
      NodePtr condition{expr()};
      expect(TokenType::PAREN_CLOSE, ")");

      newline_opt();

      // TODO: Figure out a way to distinguish between a NodeListPtr and a
      // NodePtr Possibly have a flatten or convert method, that uses dynamic
      // cast?
      NodeListPtr body;
      if(auto ptr{t_body()}; ptr) {
        body = std::make_unique<List>();
        body->push_back(std::move(ptr));
      }

      node = std::make_unique<While>(std::move(condition), std::move(body));
      break;
    }

    case TokenType::FOR: {
      TRACE_PRINT(LogLevel::INFO, "Found FOR");

      expect(TokenType::PAREN_OPEN, "(");

      // TODO: Find a better way of doing this
      bool membership{false};
      if(next_if(TokenType::IDENTIFIER)) {
        if(next_if(TokenType::IN)) {
          TRACE_PRINT(LogLevel::INFO, "Found FOR IN");

          membership = true;
          const auto array{expect(TokenType::IDENTIFIER, "identifier")};
        } else {
          prev();
        }
      }

      if(!membership) {
        if(auto ptr{simple_statement_opt()}; ptr) {
          TRACE_PRINT(LogLevel::INFO, "Found FOR(;;)");

          expect(TokenType::SEMICOLON, ";");
          expr_opt();
          expect(TokenType::SEMICOLON, ";");
          simple_statement_opt();
        }
      }

      expect(TokenType::PAREN_CLOSE, ")");
      newline_opt();

      NodeListPtr body;
      if(auto ptr{t_body()}; ptr) {
        body = std::make_unique<List>();
        body->push_back(std::move(ptr));
      }

      newline_opt();
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}


auto AwkParser::non_unary_print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NON UNARY PRINT EXPR");
  NodePtr node;
  NodePtr nupe;

  const auto lambda = [&]() {
    return this->print_expr();
  };

  if(auto ptr{grouping()}; ptr) {
    nupe = std::move(ptr);
  } else if(auto ptr{negation(lambda)}; ptr) {
    nupe = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    nupe = std::move(ptr);
  } else if(auto ptr{prefix_operator()}; ptr) {
    nupe = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    nupe = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    if(auto ulval{universal_lvalue(ptr, lambda)}; ulval) {
      nupe = std::move(ulval);
    } else {
      nupe = std::move(ptr);
    }
  }

  // If it is indeed a non unary expression than check if is a string
  // Concatenation or a binary operator
  if(nupe) {
    if(auto rhs{non_unary_print_expr()}; rhs) {
      TRACE_PRINT(LogLevel::INFO, "Found STRING CONCAT");
      node =
        std::make_unique<StringConcatenation>(std::move(nupe), std::move(rhs));
    } else if(auto ptr{universal_print_expr(nupe, lambda)}; ptr) {
      node = std::move(ptr);
    } else {
      // If we cant find a bigger nupe expression just return the nupe
      node = std::move(nupe);
    }
  }

  return node;
}

auto AwkParser::unary_print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNARY PRINT EXPR");
  NodePtr node;

  const auto lambda = [&]() -> NodePtr {
    return this->expr();
  };

  if(auto lhs{unary_prefix(lambda)}; lhs) {
    const auto print_lambda = [&]() -> NodePtr {
      return this->print_expr();
    };

    if(auto ptr{universal_print_expr(lhs, print_lambda)}; ptr) {
      node = std::move(ptr);
    } else {
      node = std::move(lhs);
    }
  }

  return node;
}

auto AwkParser::print_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "PRINT EXPR");
  NodePtr node;

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

  if(nodes->empty()) {
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

auto AwkParser::non_unary_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NON UNARY EXPR");
  NodePtr node;
  NodePtr nue;

  const auto lambda = [&]() {
    return this->expr();
  };

  if(auto ptr{grouping()}; ptr) {
    nue = std::move(ptr);
  } else if(auto ptr{negation(lambda)}; ptr) {
    nue = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    nue = std::move(ptr);
  } else if(auto ptr{prefix_operator()}; ptr) {
    nue = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    nue = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    if(auto ulval{universal_lvalue(ptr, lambda)}; ulval) {
      nue = std::move(ulval);
    } else {
      nue = std::move(ptr);
    }
  } else if(auto ptr{non_unary_input_function()}; ptr) {
    nue = std::move(ptr);
  }

  // If it is indeed a non unary expression than check if is a string
  // Concatenation or a binary operator
  if(nue) {
    if(auto rhs{non_unary_expr()}; rhs) {
      TRACE_PRINT(LogLevel::INFO, "Found STRING CONCAT");
      node =
        std::make_unique<StringConcatenation>(std::move(nue), std::move(rhs));
    } else if(auto ptr{universal_expr(nue, lambda)}; ptr) {
      node = std::move(ptr);
    } else {
      // If we cant find a bigger nue expression just return the nue
      node = std::move(nue);
    }
  }

  return node;
}

auto AwkParser::unary_expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNARY EXPR");
  NodePtr node;

  const auto lambda = [&]() -> NodePtr {
    return this->expr();
  };

  if(auto lhs{unary_prefix(lambda)}; lhs) {

    const auto print_lambda = [&]() -> NodePtr {
      return this->print_expr();
    };

    if(auto ptr{universal_expr(lhs, print_lambda)}; ptr) {
      node = std::move(ptr);
    } else {
      node = std::move(lhs);
    }
  }

  return node;
}

auto AwkParser::expr() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "EXPR");
  NodePtr node;

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

auto AwkParser::multiple_expr_list() -> NodeListPtr
{
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

  if(nodes->empty()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  // TODO: If we only have one node in the list flatten it to a single NodePtr

  return nodes;
}

auto AwkParser::expr_list() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST");
  NodeListPtr nodes;

  // multiple_expr_list allows one or multiple expr
  if(auto ptr{multiple_expr_list()}; ptr) {
    nodes = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return nodes;
}

auto AwkParser::expr_list_opt() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "EXPR LIST OPT");

  return expr_list();
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
// TODO: Figure this one out
auto AwkParser::output_redirection(NodePtr& t_lhs) -> NodePtr
{
  TRACE(LogLevel::DEBUG, "OUTPUT REDIRECTION");
  NodePtr node;

  // TODO: Have Redirection automatically convert TokenType to the correct
  // RedirectionOp
  const auto lambda{[&](RedirectionOp t_op) {
    auto rhs{expr()};
    if(!rhs)
      throw std::runtime_error{"Expected Expression after REDIRECTION"};

    return std::make_unique<Redirection>(t_op, std::move(t_lhs),
                                         std::move(rhs));
  }};

  const auto token{next()};
  switch(token.type()) {
    case TokenType::TRUNC:
      node = lambda(RedirectionOp::TRUNC);
      break;

    case TokenType::APPEND:
      node = lambda(RedirectionOp::APPEND);
      break;

    case TokenType::PIPE:
      node = lambda(RedirectionOp::PIPE);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto AwkParser::simple_print_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE PRINT STATEMENT");
  NodePtr node;

  // Convenience lambda
  const auto lambda = [&]() -> NodeListPtr {
    NodeListPtr node;

    // FIXME: This breaks ternary expressions in print statements
    // Multiple_expr_lists need more than atleast on arg, ternary expressions
    // Can be distinguished by having only one conditional argument or similar
    // Lookahead is necessary?
    // We have a similar issue with output redirection.
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
  NodePtr node;

  if(auto ptr{simple_print_statement()}; ptr) {
    node = std::move(ptr);

    if(auto redirection_ptr{output_redirection(ptr)}; redirection_ptr) {
      node = std::move(redirection_ptr);
    }
  }

  return node;
}

// TODO: Do list rule
// simple_statement : Delete NAME '[' expr_list ']'
auto AwkParser::simple_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SIMPLE STATEMENT");
  NodePtr node;

  if(next_if(TokenType::DELETE)) {
    auto name{expect(TokenType::IDENTIFIER, "Name")};
    expect(TokenType::BRACE_OPEN, "[");
    auto list{expr_list()};
    expect(TokenType::BRACE_CLOSE, "]");

    node = std::make_unique<Delete>(name.value<std::string>(), std::move(list));
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
  NodePtr node;

  const auto keyword{next()};
  switch(keyword.type()) {
    case TokenType::BREAK:
      node = std::make_unique<Break>();
      break;

    case TokenType::CONTINUE:
      node = std::make_unique<Continue>();
      break;

    case TokenType::NEXT:
      node = std::make_unique<Next>();
      break;

    case TokenType::EXIT:
      node = std::make_unique<Exit>(expr_opt());
      break;

    case TokenType::RETURN:
      node = std::make_unique<Return>(expr_opt());
      break;

    case TokenType::DO:
      newline_opt();
      terminated_statement();
      expect(TokenType::WHILE, "while");
      expect(TokenType::PAREN_OPEN, "(");
      expr();
      expect(TokenType::PAREN_CLOSE, ")");

      // TODO: Implement Do while
      LOG_PRINTLN("WARNING: Do While loops are not yet implemented!");
      node = std::make_unique<Nil>();
      break;

    default:
      prev();
      break;
  }

  if(!node) {
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
// TODO: Refactor
auto AwkParser::unterminated_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "UNTERMINATED STATEMENT");
  NodePtr node;

  const auto lambda{[&]() {
    return this->unterminated_statement();
  }};

  if(next_if(TokenType::IF)) {
    TRACE_PRINT(LogLevel::INFO, "Found IF");
    // TODO: Adjust grouping() to something more general?
    expect(TokenType::PAREN_OPEN, "(");
    NodePtr condition{expr()};
    expect(TokenType::PAREN_CLOSE, ")");

    newline_opt();
    if(auto ptr{unterminated_statement()}; ptr) {
      node = std::make_unique<If>(std::move(condition), std::move(ptr));
    } else if(auto then{terminated_statement()}; then) {
      expect(TokenType::ELSE, "else");
      newline_opt();
      node = std::make_unique<If>(std::move(condition), std::move(then),
                                  unterminated_statement());
    }
  } else if(auto ptr{loop(lambda)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{terminatable_statement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// TODO: Refactor
auto AwkParser::terminated_statement() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "TERMINATED STATEMENT");
  NodePtr node;

  const auto lambda{[&]() {
    return this->terminated_statement();
  }};

  if(auto ptr{action()}; ptr) {
    newline_opt();

    node = std::move(ptr);
  } else if(next_if(TokenType::IF)) {
    TRACE_PRINT(LogLevel::INFO, "Found IF");

    expect(TokenType::PAREN_OPEN, "(");
    NodePtr condition{expr()};
    expect(TokenType::PAREN_CLOSE, ")");

    newline_opt();
    NodePtr then{terminated_statement()};

    if(next_if(TokenType::ELSE)) {
      newline_opt();
      node = std::make_unique<If>(std::move(condition), std::move(then),
                                  terminated_statement());
    } else {
      node = std::make_unique<If>(std::move(condition), std::move(then));
    }
  } else if(auto ptr{loop(lambda)}; ptr) {
    node = std::move(ptr);
  } else if(next_if(TokenType::SEMICOLON)) {
    newline_opt();

    node = std::make_unique<Nil>();
  } else if(auto ptr{terminatable_statement()}; ptr) {
    if(tokentype::is_terminator(get_token().type())) {
      next();
    } else {
      throw std::runtime_error{"Expected a terminator!!!"};
    }
    newline_opt();

    node = std::move(ptr);
  }

  return node;
}

// This rule is made to match atleast one unterminated statement
// Unterminated statements end on a -> '\n'
auto AwkParser::unterminated_statement_list() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "UNTERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    if(auto ptr{unterminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  // if(nodes->empty()) {
  //   throw std::runtime_error{"expected atleast on expr in expr_list"};
  // }

  return nodes;
}

// This rule is made to match atleast one terminated statement
// Terminated statements end on a -> ';'
auto AwkParser::terminated_statement_list() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "TERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    if(auto ptr{terminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  // if(nodes->empty()) {
  //   throw std::runtime_error{"expected atleast on expr in expr_list"};
  // }

  // Create a NodeListPtr from the NodePtrList
  return nodes;
}

auto AwkParser::terminator() -> void
{
  TRACE(LogLevel::DEBUG, "TERMINATOR");

  const auto token{next()};
  if(!tokentype::is_terminator(token.type())) {
    throw std::runtime_error{"Expected either a NEWLINE or SEMICOLON"};
  }

  newline_opt();
}

auto AwkParser::action() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "ACTION");
  NodeListPtr node;

  if(next_if(TokenType::ACCOLADE_OPEN)) {
    TRACE_PRINT(LogLevel::INFO, "Found '{'");

    newline_opt();

    if(auto ptr{terminated_statement_list()}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{unterminated_statement_list()}; ptr) {
      node = std::move(ptr);
    } else {
      // node = std::make_unique<List>();
    }

    expect(TokenType::ACCOLADE_CLOSE, "}");
    TRACE_PRINT(LogLevel::INFO, "Found '}'");
  }

  return node;
}

auto AwkParser::special_pattern() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "SPECIAL PATTERN");
  NodePtr node;

  if(next_if(TokenType::BEGIN)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'BEGIN'");

    node = std::make_unique<SpecialPattern>(SpecialPatternOp::BEGIN);

  } else if(next_if(TokenType::END)) {
    TRACE_PRINT(LogLevel::INFO, "Found 'END'");

    node = std::make_unique<SpecialPattern>(SpecialPatternOp::END);
  }

  return node;
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto AwkParser::normal_pattern() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "NORMAL PATTERN");
  NodePtr node;

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
  NodePtr node;

  if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{special_pattern()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto AwkParser::param_list() -> NodeListPtr
{
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

  if(nodes->empty()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  return nodes;
}

auto AwkParser::param_list_opt() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "PARAM LIST OPT");

  return param_list();
}

auto AwkParser::item() -> NodePtr
{
  TRACE(LogLevel::DEBUG, "ITEM");
  NodePtr node;

  if(auto ptr{action()}; ptr) {
    node = std::move(ptr);
    // We must check for function first or else the function will be
    // interpreted As a pattern
  } else if(auto ptr{function()}; ptr) {
    node = std::move(ptr);
  } else if(auto pattern_ptr{pattern()}; pattern_ptr) {
    if(auto action_ptr{action()}; action_ptr) {
      node =
        std::make_unique<Recipe>(std::move(pattern_ptr), std::move(action_ptr));
    } else {
      // TODO: Properly throw later
      throw std::runtime_error{"Expected an ITEM"};
    }

    // Resolve this?
    // How should we represent this in AST?
  } else if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// item list exists out of an item followed by a terminator
// Till there are are no more items
auto AwkParser::item_list() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "ITEM LIST");
  NodeListPtr nodes{std::make_unique<List>()};

  while(!eos()) {
    // Remove newlines before items
    // TODO: Figure out if this works as intended, since its not in the
    // grammar
    newline_opt();

    if(auto ptr{item()}; ptr) {
      nodes->push_back(std::move(ptr));
      terminator();
    } else {
      break;
    }
  }

  return nodes;
}

auto AwkParser::program() -> NodeListPtr
{
  TRACE(LogLevel::DEBUG, "PROGRAM");

  NodeListPtr nodes{item_list()};

  // program must have atleast one item
  if(nodes->empty()) {
    // TODO: Error handling
  }

  return nodes;
}

auto AwkParser::parse() -> Ast
{
  LOG_PRINTLN("=== PARSING ===");

  Ast ast;
  NodePtr node{program()};

  if(node) {
    LOG_PRINTLN();
    LOG_PRINTLN("--- Print AST ---");

    node->accept(&m_visitor);
  }

  LOG_PRINTLN();

  return ast;
}
