#ifndef COMPARISON_H
#define COMPARISON_H

#include "binary_operator.hpp"
#include "operators.hpp"

// LessThan:
class LessThan : public operators::BinaryOperator {
  public:
  LessThan(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~LessThan();
};

// LessThanEqual:
class LessThanEqual : public operators::BinaryOperator {
  public:
  LessThanEqual(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~LessThanEqual();
};

// NotEqual:
class NotEqual : public operators::BinaryOperator {
  public:
  NotEqual(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~NotEqual();
};

// Equal:
class Equal : public operators::BinaryOperator {
  public:
  Equal(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Equal();
};

// GreaterThan:
class GreaterThan : public operators::BinaryOperator {
  public:
  GreaterThan(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~GreaterThan();
};

// GreaterThanEqual:
class GreaterThanEqual : public operators::BinaryOperator {
  public:
  GreaterThanEqual(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~GreaterThanEqual();
};

#endif // COMPARISON_H
