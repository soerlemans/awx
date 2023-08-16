#include "pratt_parser.hpp"

// STL Includes:
#include <memory>
#include <stdexcept>

// Includes:
#include "../../debug/log.hpp"
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

// Expression terminals:
//! Parses unary prefixes like having a + or - before an expression
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
        syntax_error("Expected an expression after + or -");
      }

      node = std::make_shared<UnaryPrefix>(token.type(), std::move(rhs));
      break;
    }

    default:
      prev();
      break;
  }

  return node;
}

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
      syntax_error("After a negation (!) an expression must follow");
    }
  }

  return node;
}

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

		// FIXME: Field reference with match expression prints field reference only
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

// TODO: We should use PostfixMap?
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

//! Prefix operator parses prefix increment and decrement
auto PrattParser::precrement() -> NodePtr
{
  DBG_TRACE(VERBOSE, "PREFIX OPERATOR");
  NodePtr node;

  const auto lambda{[&]<typename T>() {
    if(auto ptr{lvalue()}; ptr) {
      node = std::make_shared<T>(std::move(ptr), true);
    } else {
      // TODO: Error handling
    }
  }};

  switch(next().type()) {
    case TokenType::INCREMENT: {
      DBG_TRACE_PRINT(INFO, "Found ++INCREMENT");
      lambda.template operator()<Increment>();
      break;
    }

    case TokenType::DECREMENT: {
      DBG_TRACE_PRINT(INFO, "Found --DECREMENT");
      lambda.template operator()<Decrement>();
      break;
    }

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

// TODO: Add precedence climbing to membership
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

  if(t_lhs) {
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
  }

  return node;
}

// FIXME: simple_print_statement has a rule that conflicts and does not make
// It possible to detect if it is a print() or print () ? : ;
auto PrattParser::ternary(NodePtr& t_lhs, const BpFunc& t_fn,
                          const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "TERNARY");
  NodePtr node;

  if(t_lhs) {
    const auto [lbp, rbp] = m_infix.at(TokenType::QUESTION_MARK);

    if(lbp >= t_min_bp) {
      if(next_if(TokenType::QUESTION_MARK)) {
        DBG_TRACE(VERBOSE, "Found TERNARY");
        NodePtr then_ptr{t_fn(t_min_bp)};
        if(!then_ptr) {
          syntax_error("Expected expression after '?' in ternary");
        }

        expect(TokenType::COLON, ":");
        NodePtr else_ptr{t_fn(t_min_bp)};
        if(!else_ptr) {
          syntax_error("Expected expression after ':' in ternary");
        }

        node = std::make_shared<Ternary>(std::move(t_lhs), std::move(then_ptr),
                                         std::move(else_ptr));
      }
    }
  }

  return node;
}

auto PrattParser::comparison(NodePtr& t_lhs, const PrattFunc& t_fn) -> NodePtr
{
  DBG_TRACE(VERBOSE, "COMPARISON");
  NodePtr node;

  if(t_lhs) {
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
  }

  return node;
}

auto PrattParser::string_concat(NodePtr& t_lhs, const BpFunc& t_rhs,
                                const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "STRING CONCATENATION");
  NodePtr node;

  if(t_lhs) {
    // No infix token means that we are dealing with string concatenation
    const auto [lbp, rbp] = m_infix.at(TokenType::NONE);

    if(lbp >= t_min_bp) {
      if(auto rhs{t_rhs(rbp)}; rhs) {
        DBG_TRACE(INFO, "Found 'string concatenation'!");
        node = std::make_shared<StringConcatenation>(std::move(t_lhs),
                                                     std::move(rhs));
      }
    }
  }

  return node;
}

auto PrattParser::universal_infix(NodePtr& t_lhs, const PrattFunc& t_fn)
  -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL EXPR");
  NodePtr node;

  if(t_lhs) {
    // TODO: Add membership and ternary
    if(auto ptr{arithmetic(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{match(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{logical(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{membership(t_lhs)}; ptr) {
      node = std::move(ptr);
    }
  }

  return node;
}

auto PrattParser::universal_non_unary_expr(const BpFunc& t_expr_fn,
                                           const InfixFunc& t_infix_fn,
                                           const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL NON UNARY EXPR");
  NodePtr lhs;

  const auto prefix{[&](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return t_expr_fn(rbp);
  }};

  if(auto ptr{grouping()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{negation(prefix)}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{literal()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{lvalue()}; ptr) {
    lhs = std::move(ptr);

    ptr = postcrement(lhs);
    if(ptr) {
      lhs = std::move(ptr);
    }
  } else if(auto ptr{precrement()}; ptr) {
    lhs = std::move(ptr);
  } else if(auto ptr{function_call()}; ptr) {
    lhs = std::move(ptr);
  }

  // Infix:
  while(!eos()) {
    const auto infix{[&](TokenType t_type) {
      NodePtr rhs;

      const auto [lbp, rbp] = m_infix.at(t_type);
      if(lbp < t_min_bp) {
        prev();
      } else {
        rhs = t_expr_fn(rbp);
        if(!rhs) {
          syntax_error("Infix operations require a right hand side");
        }
      }

      return rhs;
    }};

    // If we do not find the expression quit
    if(auto ptr{universal_infix(lhs, infix)}; ptr) {
      lhs = std::move(ptr);
    } else if(auto ptr{assignment(lhs, infix)}; ptr) {
      lhs = std::move(ptr);
    } else if(auto ptr{t_infix_fn(lhs, infix)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
    }
  }

  return lhs;
}

auto PrattParser::universal_unary_expr(const BpFunc& t_expr_fn,
                                       const InfixFunc& t_infix_fn,
                                       int t_min_bp) -> node::NodePtr
{
  DBG_TRACE(VERBOSE, "UNIVERSAL UNARY EXPR");
  NodePtr lhs;

  // Prefix:
  const auto prefix{[&](TokenType t_type) {
    const auto [lbp, rbp] = m_prefix.at(t_type);

    return t_expr_fn(rbp);
  }};

  if(auto ptr{unary_prefix(prefix)}; ptr) {
    lhs = std::move(ptr);
  }

  // Infix:
  while(!eos()) {
    const auto infix{[&](TokenType t_type) {
      NodePtr rhs;

      const auto [lbp, rbp] = m_infix.at(t_type);
      if(lbp < t_min_bp) {
        prev();
      } else {
        rhs = t_expr_fn(rbp);
        if(!rhs) {
          syntax_error("Infix operations require a right hand side");
        }
      }

      return rhs;
    }};

    // If we do not find an infix expression quit
    if(auto ptr{universal_infix(lhs, infix)}; ptr) {
      lhs = std::move(ptr);
    } else if(auto ptr{t_infix_fn(lhs, infix)}; ptr) {
      lhs = std::move(ptr);
    } else {
      break;
    }
  }

  return lhs;
}

// Grammar:
auto PrattParser::non_unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY PRINT EXPR");

  const auto expr_fn{[this](const int t_rbp) {
    return print_expr(t_rbp);
  }};

  const auto infix_fn{
    [&](NodePtr& t_lhs, [[maybe_unused]] const PrattFunc& t_fn) {
      NodePtr node;
      const auto rhs_fn{[this](const int t_min_bp) {
        return non_unary_print_expr(t_min_bp);
      }};

      if(auto ptr{string_concat(t_lhs, rhs_fn, t_min_bp)}; ptr) {
        node = std::move(ptr);
      } else if(auto ptr{ternary(t_lhs, expr_fn, t_min_bp)}; ptr) {
        node = std::move(ptr);
      }

      return node;
    }};

  return universal_non_unary_expr(expr_fn, infix_fn, t_min_bp);
}

auto PrattParser::unary_print_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY PRINT EXPR");

  const auto expr_fn{[this](const int t_rbp) {
    return print_expr(t_rbp);
  }};

  const auto infix_fn{[&]([[maybe_unused]] NodePtr& t_lhs,
                          [[maybe_unused]] const PrattFunc& t_fn) {
    NodePtr node;
    const auto rhs_fn{[this](const int t_min_bp) {
      return non_unary_print_expr(t_min_bp);
    }};

    if(auto ptr{string_concat(t_lhs, rhs_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ternary(t_lhs, expr_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    }

    return node;
  }};

  return universal_unary_expr(expr_fn, infix_fn, t_min_bp);
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

// ;; Non unary diff
// ;; Non unary expr has these extra's
//   non_unary_input_function

// FIXME: For now this is just a copy of the code for non_unary_print_expr().
// This code should not be repeated like this
auto PrattParser::non_unary_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "NON UNARY EXPR");

  const auto expr_fn{[this](const int t_rbp) {
    return expr(t_rbp);
  }};

  const auto infix_fn{[&](NodePtr& t_lhs, const PrattFunc& t_fn) {
    NodePtr node;

    const auto rhs_fn{[this](const int t_min_bp) {
      return non_unary_expr(t_min_bp);
    }};

    if(auto ptr{comparison(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{string_concat(t_lhs, rhs_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ternary(t_lhs, expr_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{non_unary_input_function(t_lhs)}; ptr) {
      node = std::move(ptr);
    }

    return node;
  }};

  return universal_non_unary_expr(expr_fn, infix_fn, t_min_bp);
}

// ;; Unary diff
// ;; Unary expr has these extra's
//   unary_input_function

// FIXME: For now this is just a copy of the code for non_unary_print_expr().
// This code should not be repeated like this
auto PrattParser::unary_expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "UNARY EXPR");

  const auto expr_fn{[this](const int t_rbp) {
    return expr(t_rbp);
  }};

  const auto infix_fn{[&](NodePtr& t_lhs, const PrattFunc& t_fn) {
    NodePtr node;
    const auto rhs_fn{[this](const int t_min_bp) {
      return non_unary_expr(t_min_bp);
    }};

    if(auto ptr{comparison(t_lhs, t_fn)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{string_concat(t_lhs, rhs_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{ternary(t_lhs, expr_fn, t_min_bp)}; ptr) {
      node = std::move(ptr);
    } else if(auto ptr{non_unary_input_function(t_lhs)}; ptr) {
      node = std::move(ptr);
    }

    return node;
  }};

  return universal_unary_expr(expr_fn, infix_fn, t_min_bp);
}

auto PrattParser::expr(const int t_min_bp) -> NodePtr
{
  DBG_TRACE(VERBOSE, "EXPR");
  NodePtr node;

  if(auto ptr{unary_expr(t_min_bp)}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_expr(t_min_bp)}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}
