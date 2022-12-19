#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "../expression.hpp"

#include "operators.hpp"


class operators::UnaryOperator : public Expression {
protected:
  StatementPointer m_first;

public:
  explicit UnaryOperator(Precedence t_precedence, StatementPointer&& t_stmnt);

  auto first() -> StatementPointer&;

  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~UnaryOperator();
};

#endif // UNARY_OPERATOR_H
