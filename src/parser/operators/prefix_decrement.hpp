#ifndef PREFIX_DECREMENT_H
#define PREFIX_DECREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::PrefixDecrement: public operators::UnaryOperator {
public:
  PrefixDecrement(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PrefixDecrement();
};

#endif // PREFIX_DECREMENT_H
