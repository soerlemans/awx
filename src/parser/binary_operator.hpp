#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "unary_operator.hpp"


enum Associativity : u16 {
  NONE = 0,
  LEFT,
  RIGHT,
};

class BinaryOperator : public UnaryOperator {
  protected:
  StatementPointer m_right;
  Associativity m_associativity;

  public:
  explicit BinaryOperator(StatementType t_stmnttype, Precedence t_precedence,
                          StatementPointer&& t_left,
                          StatementPointer&& t_right);

  auto right() -> StatementPointer&;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~BinaryOperator();
};
#endif // BINARY_OPERATOR_H
