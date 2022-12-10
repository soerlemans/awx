#ifndef POSTFIX_DECREMENT_H
#define POSTFIX_DECREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::PostfixDecrement: public operators::UnaryOperator {
public:
  PostfixDecrement(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PostfixDecrement();
};

#endif // POSTFIX_DECREMENT_H
