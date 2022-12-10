#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "expression.hpp"


class UnaryOperator : public Expression {
protected:
  StatementPointer m_left;

public:
  explicit UnaryOperator(StatementType t_stmnttype, Precedence t_precedence, StatementPointer&& t_stmnt);

  auto left() -> StatementPointer&;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~UnaryOperator();
};

#endif // UNARY_OPERATOR_H
