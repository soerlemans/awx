#ifndef PREFIX_INCREMENT_H
#define PREFIX_INCREMENT_H

#include "operators.hpp"
#include "binary_operator.hpp"


class operators::PrefixIncrement: public operators::UnaryOperator {
public:
  PrefixIncrement(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PrefixIncrement();
};

#endif // PREFIX_INCREMENT_H
