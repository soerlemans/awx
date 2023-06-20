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
using namespace node::lvalue;
using namespace node::functions;

// Methods:
PrattParser::PrattParser(token::TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}

auto PrattParser::newline_opt() -> void
{
  DBG_TRACE(VERBOSE, "NEWLINE OPT");

  while(!eos() && next_if(TokenType::NEWLINE)) {
    DBG_TRACE_PRINT(INFO, "Found NEWLINE");
  }
}

// Parses unary prefixes like having a + or - before an expression
auto PrattParser::unary_prefix(const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY PREFIX");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    case TokenType::PLUS:
      [[fallthrough]];
    case TokenType::MINUS: {
      DBG_TRACE(VERBOSE, "Found UNARY PREFIX");

      NodePtr rhs{t_fn(token.type())};
      if(!rhs) {
        throw std::runtime_error{"Expected an expression after + or -"};
      }

      node = std::make_shared<UnaryPrefix>(token.type(), std::move(rhs));
      break;
    }

    default:
      prev();
      break;
  }

  // switch(const auto tokentype{next().type()}; tokentype) {
  //   case TokenType::PLUS:
  //     [[fallthrough]];
  //   case TokenType::MINUS: {
  //     DBG_TRACE(VERBOSE, "Found UNARY PREFIX");

  //     const auto [lbp, rbp] = m_prefix.at(tokentype);
  //     lhs = std::make_shared<UnaryPrefix>(tokentype, print_expr(rbp));
  //     break;
  //   }

  //   default:
  //     prev();
  //     break;
  // }

  return node;
}

auto PrattParser::lvalue() -> NodePtr
{
  DBG_TRACE(VERBOSE, "LVALUE");
  NodePtr node;

  const auto token{next()};
  switch(token.type()) {
    case TokenType::IDENTIFIER: {
      const auto name{token.value<std::string>()};
      // We really dont expect these next_tokens to fail
      if(next_if(TokenType::BRACE_OPEN)) {
        DBG_TRACE_PRINT(INFO, "Found ARRAY SUBSCRIPT");
        node = std::make_shared<Array>(name, expr_list());

        expect(TokenType::BRACE_CLOSE, "]");
      } else {
        DBG_TRACE_PRINT(INFO, "Found VARIABLE: ", name);
        node = std::make_shared<Variable>(name);
      }
      break;
    }

    case TokenType::DOLLAR_SIGN: {
      DBG_TRACE_PRINT(INFO, "Found FIELD REFERENCE");
      node = std::make_shared<FieldReference>(expr());
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

// ;; Unary diff
// ;; Unary expr has these extra's
//   unary_expr '<'      expr
//   unary_expr LE       expr
//   unary_expr NE       expr
//   unary_expr EQ       expr
//   unary_expr '>'      expr
//   unary_expr GE       expr
//   unary_input_function

// ;; Non unary diff
// ;; Non unary expr has these extra's
//   non_unary_expr '<'      expr
//   non_unary_expr LE       expr
//   non_unary_expr NE       expr
//   non_unary_expr EQ       expr
//   non_unary_expr '>'      expr
//   non_unary_expr GE       expr
//   non_unary_input_function

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

auto PrattParser::negation(const PrattFunc& t_expr) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NEGATION");
  NodePtr node;

  if(next_if(TokenType::NOT)) {
    DBG_TRACE_PRINT(INFO, "Found '!'");
    if(auto ptr{t_expr(TokenType::NOT)}; ptr) {
      node = std::make_shared<Not>(std::move(ptr));
    } else {
      throw std::runtime_error{
        "After a negation (!) an expression must follow"};
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

// Prefix operator parses prefix increment and decrement
auto PrattParser::precrement() -> NodePtr
{
  DBG_TRACE(VERBOSE, "PREFIX OPERATOR");
  NodePtr node;

  // TODO: Find a way to shorten or macro this?
  switch(next().type()) {
    case TokenType::INCREMENT: {
      DBG_TRACE_PRINT(INFO, "Found ++INCREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_shared<Increment>(std::move(ptr), true);
      } else {
        // TODO: Error handling
      }
      break;
    }

    case TokenType::DECREMENT: {
      DBG_TRACE_PRINT(INFO, "Found --DECREMENT");
      if(auto ptr{lvalue()}; ptr) {
        node = std::make_shared<Decrement>(std::move(ptr), true);
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

auto PrattParser::postcrement(NodePtr& t_lhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "POSTCREMENT");
  NodePtr node;

  switch(next().type()) {
    case TokenType::INCREMENT:
      DBG_TRACE_PRINT(INFO, "Found INCREMENT++");
      node = std::make_shared<Increment>(std::move(t_lhs), false);
      break;

    case TokenType::DECREMENT:
      DBG_TRACE_PRINT(INFO, "Found DECREMENT--");
      node = std::make_shared<Decrement>(std::move(t_lhs), false);
      break;

    default:
      prev();
      break;
  }

  return node;
}


// This function parses function calls, it parses builtin functions as well as
// User defined
auto PrattParser::function_call() -> NodePtr
{
  DBG_TRACE(VERBOSE, "FUNCTION CALL");
  NodePtr node;

  switch(const auto token{next()}; token.type()) {
    case TokenType::BUILTIN_FUNCTION: {
      expect(TokenType::PAREN_OPEN, "(");
      NodeListPtr args{expr_list_opt()};
      expect(TokenType::PAREN_CLOSE, ")");

      auto name{token.value<std::string>()};
      DBG_TRACE_PRINT(INFO, "Found a BUILTIN FUNCTION CALL: ", name);

      node =
        std::make_shared<BuiltinFunctionCall>(std::move(name), std::move(args));
      break;
    }

    case TokenType::FUNCTION_IDENTIFIER: {
      expect(TokenType::PAREN_OPEN, "(");
      NodeListPtr args{expr_list_opt()};
      expect(TokenType::PAREN_CLOSE, ")");

      auto name{token.value<std::string>()};
      DBG_TRACE_PRINT(INFO, "Found a FUNCTION CALL: ", name);

      node = std::make_shared<FunctionCall>(std::move(name), std::move(args));
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

// TODO: Add extra parameter for ternary expression
auto PrattParser::ternary(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "TERNARY");
  NodePtr node;

  // FIXME: simple_print_statement has a rule that conflicts and does not make
  // It possible to detect if it is a print() or print () ? : ;
  if(next_if(TokenType::QUESTION_MARK)) {
    DBG_TRACE(VERBOSE, "Found TERNARY");
    NodePtr then_ptr{t_rhs()};
    if(!then_ptr) {
      // TODO: Error handling
    }

    expect(TokenType::COLON, ":");
    NodePtr else_ptr{t_rhs()};
    if(!else_ptr) {
      // TODO: Error handling
    }

    node = std::make_shared<Ternary>(std::move(t_lhs), std::move(then_ptr),
                                     std::move(else_ptr));
  }

  return node;
}


auto PrattParser::universal_prefix(const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL PREFIX");
  NodePtr node;

  return node;
}

auto PrattParser::arithmetic(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "ARITHMETIC");
  NodePtr node;

  const auto token{next()};
  const auto lambda{[&](ArithmeticOp t_op) {
    if(auto rhs{t_fn(token.type())}; rhs) {
      node =
        std::make_shared<Arithmetic>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  // TODO: Maybe define a macro to do this cleanly?
  switch(token.type()) {
    case TokenType::CARET:
      DBG_TRACE_PRINT(INFO, "Found 'POWER'");
      lambda(ArithmeticOp::POWER);
      break;

    case TokenType::ASTERISK:
      DBG_TRACE_PRINT(INFO, "Found 'MULTIPLICATION'");
      lambda(ArithmeticOp::MULTIPLY);
      break;

    case TokenType::SLASH:
      DBG_TRACE_PRINT(INFO, "Found 'DIVISION'");
      lambda(ArithmeticOp::DIVIDE);
      break;

    case TokenType::PERCENT_SIGN:
      DBG_TRACE_PRINT(INFO, "Found 'MODULO'");
      lambda(ArithmeticOp::MODULO);
      break;

    case TokenType::PLUS:
      DBG_TRACE_PRINT(INFO, "Found 'ADDITION'");
      lambda(ArithmeticOp::ADD);
      break;

    case TokenType::MINUS:
      DBG_TRACE_PRINT(INFO, "Found 'SUBTRACTION'");
      lambda(ArithmeticOp::SUBTRACT);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::match(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  using namespace node;

  DBG_TRACE(VERBOSE, "MATCH");
  NodePtr node;

  const auto token{next()};
  const auto lambda{[&](MatchOp t_op) {
    auto rhs{t_fn(token.type())};
    if(rhs) {
      node = std::make_shared<Match>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  switch(token.type()) {
    case TokenType::ERE_MATCH:
      DBG_TRACE_PRINT(INFO, "Found '~'");
      lambda(MatchOp::MATCH);
      break;

    case TokenType::ERE_NO_MATCH:
      DBG_TRACE_PRINT(INFO, "Found '!~'");
      lambda(MatchOp::NO_MATCH);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::membership(NodePtr& t_lhs) -> NodePtr
{
  DBG_TRACE(VERBOSE, "MEMBERSHIP");
  NodePtr node;

  if(next_if(TokenType::IN)) {
    DBG_TRACE_PRINT(VERBOSE, "Found MEMBERSHIP");
    const auto name{expect(TokenType::IDENTIFIER, "NAME")};
    node =
      std::make_shared<Membership>(std::move(t_lhs), name.value<std::string>());
  }

  return node;
}

// FIXME: Always returns
auto PrattParser::logical(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "LOGICAL");
  NodePtr node;

  const auto token{next()};
  auto lambda{[&]<typename T>() {
    newline_opt();
    if(auto rhs{t_fn(token.type())}; rhs) {
      node = std::make_shared<T>(std::move(t_lhs), std::move(rhs));
    }
  }};

  switch(token.type()) {
    case TokenType::AND:
      DBG_TRACE_PRINT(INFO, "Found '&&'");
      lambda.template operator()<And>();
      break;

    case TokenType::OR:
      DBG_TRACE_PRINT(INFO, "Found '||'");
      lambda.template operator()<Or>();
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::assignment(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "ASSIGNMENT");
  NodePtr node;

  // TODO: Create an actual function for this that we can call instead of
  // Defining a separate lambda in each function
  const auto token{next()};
  const auto lambda{[&](AssignmentOp t_op) {
    auto rhs{t_fn(token.type())};
    if(rhs) {
      node =
        std::make_shared<Assignment>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  switch(token.type()) {
    case TokenType::POWER_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '^='");
      lambda(AssignmentOp::POWER);
      break;

    case TokenType::MULTIPLY_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '*='");
      lambda(AssignmentOp::MULTIPLY);
      break;

    case TokenType::DIVIDE_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '/='");
      lambda(AssignmentOp::DIVIDE);
      break;

    case TokenType::MODULO_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '%='");
      lambda(AssignmentOp::MODULO);
      break;

    case TokenType::ADD_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '+='");
      lambda(AssignmentOp::ADD);
      break;

    case TokenType::SUBTRACT_ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '-='");
      lambda(AssignmentOp::SUBTRACT);
      break;

    case TokenType::ASSIGNMENT:
      DBG_TRACE_PRINT(INFO, "Found '='");
      lambda(AssignmentOp::REGULAR);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::comparison(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "COMPARISON");
  NodePtr node;

  const auto token{next()};
  const auto lambda{[&](ComparisonOp t_op) {
    auto rhs{t_fn(token.type())};
    if(rhs) {
      node =
        std::make_shared<Comparison>(t_op, std::move(t_lhs), std::move(rhs));
    }
  }};

  switch(token.type()) {
    case TokenType::LESS_THAN:
      DBG_TRACE_PRINT(INFO, "Found '<'");
      lambda(ComparisonOp::LESS_THAN);
      break;

    case TokenType::LESS_THAN_EQUAL:
      DBG_TRACE_PRINT(INFO, "Found '<='");
      lambda(ComparisonOp::LESS_THAN_EQUAL);
      break;

    case TokenType::EQUAL:
      DBG_TRACE_PRINT(INFO, "Found '=='");
      lambda(ComparisonOp::EQUAL);
      break;

    case TokenType::NOT_EQUAL:
      DBG_TRACE_PRINT(INFO, "Found '!='");
      lambda(ComparisonOp::NOT_EQUAL);
      break;

    case TokenType::GREATER_THAN:
      DBG_TRACE_PRINT(INFO, "Found '>'");
      lambda(ComparisonOp::GREATER_THAN);
      break;

    case TokenType::GREATER_THAN_EQUAL:
      DBG_TRACE_PRINT(INFO, "Found '>='");
      lambda(ComparisonOp::GREATER_THAN_EQUAL);
      break;

    default:
      prev();
      break;
  }

  return node;
}

auto PrattParser::universal_infix(NodePtr& t_lhs, const PrattFunc& t_fn)
  -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL EXPR");
  NodePtr node;

  if(auto ptr{arithmetic(t_lhs, t_fn)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{match(t_lhs, t_fn)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{logical(t_lhs, t_fn)}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// Old AwkParser implementation
// auto AwkParser::non_unary_print_expr() -> NodePtr
// {
//   DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");
//   NodePtr node;
//   NodePtr nupe;

//   const auto lambda = [&]() {
//     return this->print_expr();
//   };

//   if(auto ptr{grouping()}; ptr) {
//     nupe = std::move(ptr);
//   } else if(auto ptr{negation(lambda)}; ptr) {
//     nupe = std::move(ptr);
//   } else if(auto ptr{literal()}; ptr) {
//     nupe = std::move(ptr);
//   } else if(auto ptr{prefix_operator()}; ptr) {
//     nupe = std::move(ptr);
//   } else if(auto ptr{function_call()}; ptr) {
//     nupe = std::move(ptr);
//   } else if(auto ptr{lvalue()}; ptr) {
//     if(auto ulval{universal_lvalue(ptr, lambda)}; ulval) {
//       nupe = std::move(ulval);
//     } else {
//       nupe = std::move(ptr);
//     }
//   }

//   // If it is indeed a non unary expression than check if is a string
//   // Concatenation or a binary operator
//   if(nupe) {
//     if(auto rhs{non_unary_print_expr()}; rhs) {
//       DBG_TRACE_PRINT(INFO, "Found STRING CONCAT");
//       node =
//         std::make_shared<StringConcatenation>(std::move(nupe),
//         std::move(rhs));
//     } else if(auto ptr{universal_print_expr(nupe, lambda)}; ptr) {
//       node = std::move(ptr);
//     } else {
//       // If we cant find a bigger nupe expression just return the nupe
//       node = std::move(nupe);
//     }
//   }

//   return node;
// }

// TODO: These precedence rules are wrong
// auto AwkParser::unary_print_expr() -> NodePtr
// {
//   DBG_TRACE(VERBOSE, "UNARY PRINT EXPR");
//   NodePtr node;

//   const auto lambda = [&]() -> NodePtr {
//     return this->expr();
//   };

//   if(auto lhs{unary_prefix(lambda)}; lhs) {
//     const auto print_lambda = [&]() -> NodePtr {
//       return this->print_expr();
//     };

//     if(auto ptr{universal_print_expr(lhs, print_lambda)}; ptr) {
//       node = std::move(ptr);
//     } else {
//       node = std::move(lhs);
//     }
//   }

//   return node;
// }

auto PrattParser::non_unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");
  NodePtr lhs;

  // Literals
  const auto unary_lambda{[this](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return print_expr(rbp);
  }};

  if(auto ptr{grouping()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{negation(unary_lambda)}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    lhs = std::move(ptr);
    if(next_if(TokenType::INCREMENT)) {
      // TODO:
    } else if(next_if(TokenType::DECREMENT)) {
      // TODO:
    }
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

  // Binary expressions:
  while(!eos()) {
    const auto lambda{[&](TokenType t_type) {
      NodePtr rhs;

      const auto [lbp, rbp] = m_infix.at(t_type);
      if(lbp < t_min_bp) {
        prev();
      } else {
        rhs = print_expr(rbp);
        if(!rhs) {
          throw std::runtime_error{
            "Binary operation requires second parameter"};
        }
      }

      return rhs;
    }};

    // If we do not find the expression quit
    if(auto ptr{universal_infix(lhs, lambda)}; ptr) {
      lhs = std::move(ptr);
    } else if(auto ptr{assignment(lhs, lambda)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
    }
  }

  return lhs;
}

auto PrattParser::unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY PRINT EXPR");
  NodePtr lhs;

  // Unary expressions:
  const auto lambda{[this](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return print_expr(rbp);
  }};

  if(auto ptr{unary_prefix(lambda)}; ptr) {
    lhs = std::move(ptr);
  }

  // Binary expressions:
  while(!eos()) {
    const auto lambda{[&](TokenType t_type) {
      NodePtr rhs;

      const auto [lbp, rbp] = m_infix.at(t_type);
      if(lbp < t_min_bp) {
        prev();
      } else {
        rhs = print_expr(rbp);
        if(!rhs) {
          throw std::runtime_error{
            "Binary operation requires second parameter"};
        }
      }

      return rhs;
    }};

    // TODO: Implement StringConcatenation, membership and ternary
    // If we do not find the expression quit
    if(auto ptr{universal_infix(lhs, lambda)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
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

auto PrattParser::multiple_expr_list() -> NodeListPtr
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
        // TODO: Error handling
      }
    } else {
      break;
    }
  }

  if(nodes->empty()) {
    // throw std::runtime_error{"expected atleast on expr in expr_list"};
  }

  // TODO: If we only have one node in the list flatten it to a single
  // NodePtr

  return nodes;
}

auto PrattParser::expr_list() -> NodeListPtr
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

auto PrattParser::expr_list_opt() -> NodeListPtr
{
  DBG_TRACE(VERBOSE, "EXPR LIST OPT");

  return expr_list();
}
