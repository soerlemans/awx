#include "awk_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Includes:
#include "../../debug/log.hpp"
#include "../../node/include.hpp"
#include "../../token/token_type.hpp"
#include "../../token/token_type_helpers.hpp"


// Macros:
//! Convenvience macro for
#define GROUPING(t_var, t_func)          \
  do {                                   \
    expect(TokenType::PAREN_OPEN, "(");  \
    t_var = t_func();                    \
    expect(TokenType::PAREN_CLOSE, ")"); \
  } while(false)

// Using statements:
using namespace parser::awk;

using namespace token;
using namespace reserved::symbols;

using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

// Constructors:
AwkParser::AwkParser(TokenStream t_tokenstream)
  : PrattParser{std::move(t_tokenstream)}
{}

// Parsing rule/grammar rules:
auto AwkParser::newline_opt() -> void
{
  DBG_TRACE(VERBOSE, "NEWLINE OPT");

  while(!eos() && next_if(TokenType::NEWLINE)) {
    DBG_TRACE_PRINT(INFO, "Found 'NEWLINE'");
  }
}


auto AwkParser::simple_get() -> NodePtr
{
  DBG_TRACE(VERBOSE, "SIMPLE GET");
  NodePtr node;

  if(next_if(TokenType::GETLINE)) {
    DBG_TRACE_PRINT(INFO, "Found GETLINE");

    node = std::make_shared<Getline>(lvalue());
  }

  return node;
}

auto AwkParser::unary_input_function() -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY INPUT FUNCTION");
  NodePtr node;

  if(NodePtr lhs{unary_expr()}; lhs) {
    expect(TokenType::PIPE, "|");

    node = std::make_shared<Redirection>(RedirectionOp::PIPE, std::move(lhs),
                                         simple_get());
  }

  return node;
}

auto AwkParser::non_unary_input_function(NodePtr& t_lhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY INPUT FUNCTION");
  NodePtr node;

  if(auto ptr{simple_get()}; ptr) {
    if(next_if(TokenType::LESS_THAN)) {
      node = std::make_shared<Redirection>(RedirectionOp::READ, std::move(ptr),
                                           expr());
    } else {
      node = std::move(ptr);
    }
  } else if(t_lhs && next_if(TokenType::PIPE)) {
    DBG_TRACE(VERBOSE, "Found 'PIPE' redirection");

    node = std::make_shared<Redirection>(RedirectionOp::PIPE, std::move(t_lhs),
                                         simple_get());
  }

  return node;
}

auto AwkParser::function() -> NodePtr
{
  DBG_TRACE(VERBOSE, "FUNCTION");
  NodePtr node;

  if(next_if(TokenType::FUNCTION)) {
    DBG_TRACE_PRINT(VERBOSE, "Found FUNCTION");

    // When defining a function a space after the identifier is allowed
    if(const auto token{get_token()}; tokentype::is_identifier(token.type())) {
      DBG_TRACE_PRINT(INFO, "Found a FUNCTION");

      next();
      const auto name{token.value<std::string>()};
      DBG_TRACE_PRINT(VERBOSE, "Valid FUNCTION IDENTIFIER: ", name);

			NodeListPtr params;
			GROUPING(params, param_list_opt);

      newline_opt();
      auto body{action()};


      node =
        std::make_shared<Function>(name, std::move(params), std::move(body));
    }
  }

  return node;
}

// TODO: Split FOR and WHILE into their own functions
auto AwkParser::loop(const ParserFunc& t_body) -> NodePtr
{
  DBG_TRACE(VERBOSE, "LOOP");
  NodePtr node;

  // TODO: Split even further?
  switch(next().type()) {
    case TokenType::WHILE: {
      DBG_TRACE_PRINT(INFO, "Found WHILE");

      auto condition{grouping()};
      newline_opt();

      // TODO: Figure out a way to distinguish between a NodeListPtr and a
      // NodePtr Possibly have a flatten or convert method, that uses dynamic
      // cast?
      NodeListPtr body;
      if(auto ptr{t_body()}; ptr) {
        body = std::make_shared<List>();
        body->push_back(std::move(ptr));
      }

      node = std::make_shared<While>(std::move(condition), std::move(body));
      break;
    }

    case TokenType::FOR: {
      DBG_TRACE_PRINT(INFO, "Found FOR");

      expect(TokenType::PAREN_OPEN, "(");

      // TODO: Find a better way of doing this
      bool membership{false};
      if(auto identifier{get_token()};
         identifier.type() == TokenType::IDENTIFIER) {
        next();
        if(next_if(TokenType::IN)) {
          DBG_TRACE_PRINT(INFO, "Found FOR IN");

          membership = true;
          auto array{expect(TokenType::IDENTIFIER, "identifier")};
          expect(TokenType::PAREN_CLOSE, ")");
          newline_opt();

          NodeListPtr body;
          if(auto ptr{t_body()}; ptr) {
            body = std::make_shared<List>();
            body->push_back(std::move(ptr));
          }

          const auto name_identifier{identifier.value<std::string>()};
          const auto name_array{array.value<std::string>()};
          node = std::make_shared<ForIn>(
            std::make_shared<Variable>(name_identifier),
            std::make_shared<Array>(name_array), std::move(body));
        } else {
          prev();
        }
      }

      if(!membership) {
        if(auto ptr{simple_statement_opt()}; ptr) {
          DBG_TRACE_PRINT(INFO, "Found FOR(;;)");

          expect(TokenType::SEMICOLON, ";");
          auto condition{expr_opt()};
          expect(TokenType::SEMICOLON, ";");
          auto post_expr{simple_statement_opt()};
          expect(TokenType::PAREN_CLOSE, ")");
          newline_opt();

          NodeListPtr body;
          if(auto ptr{t_body()}; ptr) {
            body = std::make_shared<List>();
            body->push_back(std::move(ptr));
          }

          node = std::make_shared<For>(std::move(ptr), std::move(condition),
                                       std::move(post_expr), std::move(body));
        }
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

// TODO: multiple_expr_list is very similar create a helper function that both
// Can use
auto AwkParser::print_expr_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "PRINT EXPR LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  if(auto ptr{print_expr()}; ptr) {
    DBG_TRACE_PRINT(INFO, "Found PRINT_EXPR");

    nodes->push_back(std::move(ptr));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      newline_opt();
      if(auto ptr{print_expr()}; ptr) {
        DBG_TRACE_PRINT(INFO, "Found ',' PRINT_EXPR");

        nodes->push_back(std::move(ptr));
      } else {
        // TODO: Error handling
      }
    } else {
      break;
    }
  }

  return nodes;
}

auto AwkParser::print_expr_list_opt() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "PRINT EXPR LIST OPT");

  return print_expr_list();
}

auto AwkParser::multiple_expr_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "MULTIPLE EXPR LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  if(auto ptr{expr()}; ptr) {
    DBG_TRACE_PRINT(INFO, "Found EXPR");

    nodes->push_back(std::move(ptr));
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      newline_opt();
      if(auto ptr{expr()}; ptr) {
        DBG_TRACE_PRINT(INFO, "Found ',' EXPR");

        nodes->push_back(std::move(ptr));
      } else {
        syntax_error("Expected another expression after ',");
      }
    } else {
      break;
    }
  }

  return nodes;
}

auto AwkParser::expr_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "EXPR LIST");
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
  DBG_TRACE(VERBOSE, "EXPR LIST OPT");

  return expr_list();
}

auto AwkParser::expr_opt() -> NodePtr
{
  DBG_TRACE(VERBOSE, "EXPR OPT");

  return expr();
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
// TODO: Figure this one out
auto AwkParser::output_redirection(NodePtr& t_lhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "OUTPUT REDIRECTION");
  NodePtr node;

  // TODO: Have Redirection automatically convert TokenType to the correct
  // RedirectionOp
  const auto lambda{[&](RedirectionOp t_op) {
    auto rhs{expr()};
    if(!rhs) {
      syntax_error("Expected expression after output redirection");
    }

    return std::make_shared<Redirection>(t_op, std::move(t_lhs),
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
  DBG_TRACE(VERBOSE, "SIMPLE PRINT STATEMENT");
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
    DBG_TRACE_PRINT(INFO, "Found 'print'");

    node = std::make_shared<Print>(lambda());
  } else if(next_if(TokenType::PRINTF)) {
    DBG_TRACE_PRINT(INFO, "Found 'printf");

    auto params{lambda()};
    // TODO: Improve error handling:
    if(params->size() < 1) {
      syntax_error("printf needs atleast one argument");
    }

    auto format{params->front()};
    params->pop_front();
    node = std::make_shared<Printf>(std::move(format), std::move(params));
  }

  return node;
}

auto AwkParser::print_statement() -> NodePtr
{
  DBG_TRACE(VERBOSE, "PRINT STATEMENT");
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
  DBG_TRACE(VERBOSE, "SIMPLE STATEMENT");
  NodePtr node;

  if(next_if(TokenType::DELETE)) {
    auto name{expect(TokenType::IDENTIFIER, "Name")};
    expect(TokenType::BRACE_OPEN, "[");
    auto list{expr_list()};
    expect(TokenType::BRACE_CLOSE, "]");

    node = std::make_shared<Delete>(name.value<std::string>(), std::move(list));
  } else if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{print_statement()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto AwkParser::simple_statement_opt() -> NodePtr
{
  DBG_TRACE(VERBOSE, "SIMPLE STATEMENT OPT");

  return simple_statement();
}

auto AwkParser::terminatable_statement() -> NodePtr
{
  DBG_TRACE(VERBOSE, "TERMINATABLE STATEMENT");
  NodePtr node;

  switch(next().type()) {
    case TokenType::BREAK:
      node = std::make_shared<Break>();
      break;

    case TokenType::CONTINUE:
      node = std::make_shared<Continue>();
      break;

    case TokenType::NEXT:
      node = std::make_shared<Next>();
      break;

    case TokenType::EXIT:
      node = std::make_shared<Exit>(expr_opt());
      break;

    case TokenType::RETURN:
      node = std::make_shared<Return>(expr_opt());
      break;

    case TokenType::DO: {
      newline_opt();
      auto body{terminated_statement()};
      expect(TokenType::WHILE, "while");
      auto condition{grouping()};

      // FIXME: Figure out this bullshit with NodeListPtr
      // node = std::make_shared<DoWhile>(std::move(condition),
      // std::move(body));
      break;
    }

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
  DBG_TRACE(VERBOSE, "UNTERMINATED STATEMENT");
  NodePtr node;

  const auto lambda{[&]() {
    return this->unterminated_statement();
  }};

  if(next_if(TokenType::IF)) {
    DBG_TRACE_PRINT(INFO, "Found IF");
    auto condition{grouping()};

    newline_opt();
    if(auto ptr{unterminated_statement()}; ptr) {
      node = std::make_shared<If>(std::move(condition), std::move(ptr));
    } else if(auto then{terminated_statement()}; then) {
      expect(TokenType::ELSE, "else");
      newline_opt();
      node = std::make_shared<If>(std::move(condition), std::move(then),
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
  DBG_TRACE(VERBOSE, "TERMINATED STATEMENT");
  NodePtr node;

  const auto lambda{[&]() {
    return this->terminated_statement();
  }};

  if(auto ptr{action()}; ptr) {
    newline_opt();

    node = std::move(ptr);
  } else if(next_if(TokenType::IF)) {
    DBG_TRACE_PRINT(INFO, "Found IF");

    auto condition{grouping()};
    newline_opt();
    auto then{terminated_statement()};

    if(next_if(TokenType::ELSE)) {
      newline_opt();
      node = std::make_shared<If>(std::move(condition), std::move(then),
                                  terminated_statement());
    } else {
      node = std::make_shared<If>(std::move(condition), std::move(then));
    }
  } else if(auto ptr{loop(lambda)}; ptr) {
    node = std::move(ptr);
  } else if(next_if(TokenType::SEMICOLON)) {
    newline_opt();

    node = std::make_shared<Nil>();
  } else if(auto ptr{terminatable_statement()}; ptr) {
    if(tokentype::is_terminator(get_token().type())) {
      next();
    } else {
      syntax_error("Expected a terminator");
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
  DBG_TRACE(VERBOSE, "UNTERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  while(!eos()) {
    if(auto ptr{unterminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  return nodes;
}

// This rule is made to match atleast one terminated statement
// Terminated statements end on a -> ';'
auto AwkParser::terminated_statement_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "TERMINATED STATEMENT LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  while(!eos()) {
    if(auto ptr{terminated_statement()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  return nodes;
}

auto AwkParser::terminator() -> void
{
  DBG_TRACE(VERBOSE, "TERMINATOR");

  const auto token{next()};
  if(!tokentype::is_terminator(token.type())) {
    syntax_error("Expected a terminator");
  }

  newline_opt();
}

auto AwkParser::action() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "ACTION");
  NodeListPtr node;

  if(next_if(TokenType::ACCOLADE_OPEN)) {
    DBG_TRACE_PRINT(INFO, "Found '{'");

    newline_opt();

    // Have a way to restore the position of the tokenstream when an expression
    // is unterminated, after parsing it to the end
    if(auto ptr{terminated_statement_list()}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{unterminated_statement_list()}; ptr) {
      node = std::move(ptr);
    } else {
      // node = std::make_shared<List>();
    }

    expect(TokenType::ACCOLADE_CLOSE, "}");
    DBG_TRACE_PRINT(INFO, "Found '}'");
  }

  return node;
}

auto AwkParser::special_pattern() -> NodePtr
{
  DBG_TRACE(VERBOSE, "SPECIAL PATTERN");
  NodePtr node;

  if(next_if(TokenType::BEGIN)) {
    DBG_TRACE_PRINT(INFO, "Found 'BEGIN'");

    node = std::make_shared<SpecialPattern>(SpecialPatternOp::BEGIN);

  } else if(next_if(TokenType::END)) {
    DBG_TRACE_PRINT(INFO, "Found 'END'");

    node = std::make_shared<SpecialPattern>(SpecialPatternOp::END);
  }

  return node;
}

auto AwkParser::normal_pattern() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "NORMAL PATTERN");
  NodeListPtr nodes{std::make_shared<List>()};

  if(auto ptr{expr()}; ptr) {
    nodes->push_back(std::move(ptr));

    if(next_if(TokenType::COMMA)) {
      newline_opt();
      nodes->push_back(expr());
    }
  }

  return nodes;
}

auto AwkParser::pattern() -> NodePtr
{
  DBG_TRACE(VERBOSE, "PATTERN");
  NodePtr node;

  if(auto ptr{special_pattern()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{normal_pattern()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

auto AwkParser::param_list() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "PARAM LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  if(const auto token{next()}; token.type() == TokenType::IDENTIFIER) {
    DBG_TRACE_PRINT(INFO, "Found NAME");

    nodes->push_back(std::make_shared<Variable>(token.value<std::string>()));
  } else {
    prev();
  }

  while(!eos()) {
    if(next_if(TokenType::COMMA)) {
      DBG_TRACE_PRINT(INFO, "Found ',' NAME");
      const auto token{expect(TokenType::IDENTIFIER, "NAME")};

      nodes->push_back(std::make_shared<Variable>(token.value<std::string>()));
    } else {
      break;
    }
  }

  return nodes;
}

auto AwkParser::param_list_opt() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "PARAM LIST OPT");

  return param_list();
}

auto AwkParser::item() -> NodePtr
{
  DBG_TRACE(VERBOSE, "ITEM");
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
        std::make_shared<Recipe>(std::move(pattern_ptr), std::move(action_ptr));
    } else {
      syntax_error("Expected body after a toplevel rule");
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
  DBG_TRACE(VERBOSE, "ITEM LIST");
  NodeListPtr nodes{std::make_shared<List>()};

  while(!eos()) {
    // Remove newlines before items
    newline_opt();

    // Exit if we are at the end of stream
    if(eos()) {
      break;
    }

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
  DBG_TRACE(VERBOSE, "PROGRAM");

  return item_list();
}

auto AwkParser::parse() -> NodePtr
{
  return program();
}
