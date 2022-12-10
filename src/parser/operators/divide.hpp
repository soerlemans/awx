#ifndef DIVIDE_H
#define DIVIDE_H

#include "binary_operator.hpp"

class Divide : public BinaryOperator {
public:
  Divide(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Divide();
};

#endif // DIVIDE_H
