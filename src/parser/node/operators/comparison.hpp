#ifndef COMPARISON_H
#define COMPARISON_H

#include "binary_operator.hpp"
#include "operators.hpp"

// LessThan:
class LessThan : public operators::BinaryOperator {
  public:
  LessThan(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~LessThan();
};

// LessThanEqual:
class LessThanEqual : public operators::BinaryOperator {
  public:
  LessThanEqual(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~LessThanEqual();
};

// NotEqual:
class NotEqual : public operators::BinaryOperator {
  public:
  NotEqual(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~NotEqual();
};

// Equal:
class Equal : public operators::BinaryOperator {
  public:
  Equal(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Equal();
};

// GreaterThan:
class GreaterThan : public operators::BinaryOperator {
  public:
  GreaterThan(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~GreaterThan();
};

// GreaterThanEqual:
class GreaterThanEqual : public operators::BinaryOperator {
  public:
  GreaterThanEqual(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~GreaterThanEqual();
};

#endif // COMPARISON_H
