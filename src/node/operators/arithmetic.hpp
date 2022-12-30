#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "binary_operator.hpp"
#include "operators.hpp"


// Power:
class operators::Power : public operators::BinaryOperator
{
  public:
  Power(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Power();
};

// Multiply:
class operators::Multiply : public operators::BinaryOperator
{
  public:
  Multiply(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Multiply();
};

// Divide:
class operators::Divide : public operators::BinaryOperator
{
  public:
  Divide(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Divide();
};

// Modulo:
class operators::Modulo : public operators::BinaryOperator
{
  public:
  Modulo(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Modulo();
};

// Add:
class operators::Add : public operators::BinaryOperator
{
  public:
  Add(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Add();
};

// Subtract:
class operators::Subtract : public operators::BinaryOperator
{
  public:
  Subtract(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Subtract();
};
#endif // ARITHMETIC_H
