#ifndef AWX_PARSER_SHUNTING_YARD_HPP
#define AWX_PARSER_SHUNTING_YARD_HPP

// STL Includes:
#include <queue>
#include <stack>
#include <unordered_map>

// Includes:
#include "../token/token.hpp"


namespace parser {
// Enums:
enum Associativity {
  NONE = 0,
  LEFT,
  RIGHT,
};

enum Precedence {
  GROUPING = 0,        // (a)
  FIELD_REFERENCE,     // $a
  POSTFIX_INC_DEC,     // a++, a--
  PREFIX_INC_DEC,      // ++a, --a
  POWER,               // a ^ b
  UNARY_PREFIX,        // !a, +a, -a
  ARITHMETIC_MU_DI_MO, // a * b, a / b, a % b (Multiply, Divide, Modulo)
  ARITHMETIC_ADD_SUB,  // a + b, a - b (Addition, Subtraction)
  STRING_CONCAT,       // a b
  COMPARISON,          // a < b, a <= b, a != b, a == b, a > b, a >= b
  MATCH,               // a ~ b, a ~! b (Extended Regular Expression)
  MEMBERSHIP,          // a in b, (a) in b
  LOGICAL_AND,         // a && b
  LOGICAL_OR,          // a || b
  TERNARY,             // a ? b : c
  ASSIGNMENT,          // a ^= b, a %= b, a *= b, a /= b, a += b, a -= b, a = b
};

// Structs:
struct Operator {
  Precedence m_precedence;
  Associativity m_associativity;
};

// TODO: Place in namespace?
std::unordered_map<token::TokenType, Operator> g_operators = {
  {token::TokenType::CARET, {Precedence::POWER, RIGHT}},
};

// Classes:
/*! This class implements the shunting yard algorithm.
 */
class ShuntingYard {
  private:
  std::stack<token::Token> m_stack;
  std::queue<token::Token> m_input, m_output;

  public:
  ShuntingYard() = default;

  auto push(const Token& t_token) -> void;
  auto process() -> void;

  virtual ~ShuntingYard() = default;
};
} // namespace parser


#endif // AWX_PARSER_SHUNTING_YARD_HPP
