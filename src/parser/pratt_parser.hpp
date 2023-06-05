#ifndef AWX_PARSER_PRATT_PARSER_HPP
#define AWX_PARSER_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Local Includes:
#include "parser.hpp"


namespace parser {
// Aliases:
//! Two integers are used to indicate the binding power
using BindingPower = std::pair<int, int>;

// Enums:
//! Operators that have precedence
enum class Precedence {
  // Highest precedence
  GROUPING,         // (expr )
  FIELD_REFERENCE,  // $expr
  POST_CREMENT,     // lvalue++, lvalue--
  PRE_CREMENT,      // ++lvalue, --lvalue
  EXPONENTATION,    // expr ^ expr
  UNARY_OP,         // !expr, +expr, -expr
  FACTOR,           // expr * expr, expr / expr, expr % expr
  BINARY,           // expr + expr, expr - expr
  STRING_CONCAT,    // expr expr
  COMPARISON,       // expr <=> expr
  MATCH,            // expr ~ expr, expr !~ expr
  ARRAY_MEMBERSHIP, // expr in expr
  AND,              // expr && expr
  OR,               // expr || expr
  CONDITIONAL,      // expr ? expr : expr

  // expr ^= expr, expr *= expr, expr /= expr, expr %= expr, expr += expr,
  //	expr -= expr
  ASSIGNMENT,
  // Lowest precedence
};

// Functions:
//! Note not all TokenType's can be converted to a Precedence enums
constexpr auto tokentype2precedence(const token::TokenType t_type) -> Precedence
{
  using namespace token;

  switch(t_type) {
    case TokenType::DOLLAR_SIGN:
      return Precedence::FIELD_REFERENCE;

    case TokenType::CARET:
      return Precedence::EXPONENTATION;

    case TokenType::ASTERISK:
      [[fallthrough]];
    case TokenType::SLASH:
      [[fallthrough]];
    case TokenType::PERCENT_SIGN:
      return Precedence::FACTOR;

    case TokenType::LESS_THAN:
      [[fallthrough]];
    case TokenType::LESS_THAN_EQUAL:
      [[fallthrough]];
    case TokenType::EQUAL:
      [[fallthrough]];
    case TokenType::NOT_EQUAL:
      [[fallthrough]];
    case TokenType::GREATER_THAN:
      [[fallthrough]];
    case TokenType::GREATER_THAN_EQUAL:
      return Precedence::COMPARISON;

    case TokenType::IN:
      return Precedence::ARRAY_MEMBERSHIP;

    case TokenType::AND:
      return Precedence::AND;

    case TokenType::OR:
      return Precedence::OR;

    case TokenType::POWER_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::MULTIPLY_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::DIVIDE_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::MODULO_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::ADD_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::SUBTRACT_ASSIGNMENT:
      [[fallthrough]];
    case TokenType::ASSIGNMENT:
      return Precedence::ASSIGNMENT;

    default:
      // TODO: Error handling
      break;
  }
}

// Classes:
class PrattParser {
  private:
  int m_min_bp;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  virtual auto infix_binding_power(Precedence t_prec) const -> BindingPower;
  virtual auto infix_binding_power(token::TokenType t_type) const
    -> BindingPower;

  virtual ~PrattParser() = default;
};
} // namespace parser

#endif // AWX_PARSER_PRATT_PARSER_HPP
