#ifndef POSTFIX_INCREMENT_H
#define POSTFIX_INCREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::PostfixIncrement: public operators::UnaryOperator {
public:
  PostfixIncrement(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PostfixIncrement();
};

#endif // POSTFIX_INCREMENT_H
