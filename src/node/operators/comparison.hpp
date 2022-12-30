#ifndef COMPARISON_H
#define COMPARISON_H

#include "binary_operator.hpp"
#include "operators.hpp"

// LessThan:
class LessThan : public operators::BinaryOperator
{
  public:
  LessThan(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~LessThan();
};

// LessThanEqual:
class LessThanEqual : public operators::BinaryOperator
{
  public:
  LessThanEqual(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~LessThanEqual();
};

// NotEqual:
class NotEqual : public operators::BinaryOperator
{
  public:
  NotEqual(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~NotEqual();
};

// Equal:
class Equal : public operators::BinaryOperator
{
  public:
  Equal(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Equal();
};

// GreaterThan:
class GreaterThan : public operators::BinaryOperator
{
  public:
  GreaterThan(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~GreaterThan();
};

// GreaterThanEqual:
class GreaterThanEqual : public operators::BinaryOperator
{
  public:
  GreaterThanEqual(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~GreaterThanEqual();
};

#endif // COMPARISON_H
