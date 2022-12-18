#ifndef TRINARY_OPERATOR_H
#define TRINARY_OPERATOR_H

#include "binary_operator.hpp"
#include "operators.hpp"

class operators::TrinaryOperator : public operators::BinaryOperator {
  protected:
  StatementPointer m_third;

  public:
  explicit TrinaryOperator(StatementType t_stmnttype, Precedence t_precedence,
                           Associativity t_associativity,
                           StatementPointer&& t_left,
                           StatementPointer&& t_middle,
                           StatementPointer&& t_right);

  auto third() -> StatementPointer&;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~TrinaryOperator();
};

#endif // TRINARY_OPERATOR_H
