#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "operators.hpp"
#include "unary_operator.hpp"


enum Associativity : u16 {
  NONE = 0,
  LEFT,
  RIGHT,
};

class operators::BinaryOperator : public operators::UnaryOperator {
  protected:
  Associativity m_associativity;
  StatementPointer m_second;

  public:
  explicit BinaryOperator(Precedence t_precedence,
                          Associativity t_associativity,
                          StatementPointer&& t_left,
                          StatementPointer&& t_right);

  auto second() -> StatementPointer&;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~BinaryOperator();
};
#endif // BINARY_OPERATOR_H
