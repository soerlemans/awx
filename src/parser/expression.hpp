#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "statement.hpp"


// TODO: Name these more accurately later
enum class Precedence : u16 {
  Grouping = 0,     // (a)
  FieldReference,   // $a
  PostfixIncDec,    // a++, a--
  PrefixIncDec,     // ++a, --a
  Power,            // a ^ b
  UnaryPrefix,      // !a, +a, -a
  ArithmeticMuDiMo, // a * b, a / b, a % b (Multiply, Divide, Modulo)
  ArithmeticAddSub, // a + b, a - b (Addition, Subtraction)
  StringConcat,     // a b
  Comparison,       // a < b, a <= b, a != b, a == b, a > b, a >= b
  ERE,              // a ~ b, a ~! b (Extended Regular Expression)
  ArrayMembership,  // a in b, (a) in b
  LogicalAnd,       // a && b
  LogicalOr,        // a || b
  ConditionalExpr,  // a ? b : c
  Assignment,       // a ^= b, a %= b, a *= b, a /= b, a += b, a -= b, a = b
};

// Have UnaryOperator and BinaryOperator derive from this
class Expression : public Statement {
protected:
  Precedence m_precedence;

public:
  Expression(StatementType t_stmnttype, Precedence t_precedence);

  auto precedence() -> Precedence;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~Expression();
};

#endif // EXPRESSION_H
