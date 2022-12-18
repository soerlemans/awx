#ifndef LOGICAL_H
#define LOGICAL_H

#include "operators.hpp"
#include "binary_operator.hpp"


// Not:
// Pay attention Not is not a BinaryOperator
class operators::Not : public operators::UnaryOperator {
  public:
  Not(StatementPointer&& t_left);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Not();
};

// And:
class operators::And : public operators::BinaryOperator {
  public:
  And(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~And();
};

// Or:
class operators::Or : public operators::BinaryOperator {
  public:
  Or(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Or();
};

#endif // LOGICAL_H
