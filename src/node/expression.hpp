#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "node_interface.hpp"


namespace node {
// Enum definitions:
// TODO: Name these more accurately later
enum class Precedence : u16 {
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

// Have UnaryOperator and BinaryOperator derive from this
class Expression : public NodeInterface {
  protected:
  Precedence m_precedence;

  public:
  Expression(Precedence t_precedence);

  auto precedence() -> Precedence;

  auto accept(NodeVisitor* t_visitor) -> void override = 0;

  ~Expression() override = default;
};
} // namespace node

#endif // EXPRESSION_HPP
