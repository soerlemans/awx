#ifndef PREFIX_INCREMENT_H
#define PREFIX_INCREMENT_H

#include "binary_operator.hpp"


class PrefixIncrement: public UnaryOperator {
public:
  PrefixIncrement(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PrefixIncrement();
};

#endif // PREFIX_INCREMENT_H
