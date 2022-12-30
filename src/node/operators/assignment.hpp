#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "binary_operator.hpp"
#include "operators.hpp"


// Power assignment:
class operators::PowerAssignment : public operators::BinaryOperator
{
  public:
  PowerAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PowerAssignment();
};

// Multiply assignment:
class operators::MultiplyAssignment : public operators::BinaryOperator
{
  public:
  MultiplyAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~MultiplyAssignment();
};

// Divide assignemnt:
class operators::DivideAssignment : public operators::BinaryOperator
{
  public:
  DivideAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~DivideAssignment();
};

// Modulo assignment:
class operators::ModuloAssignment : public operators::BinaryOperator
{
  public:
  ModuloAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~ModuloAssignment();
};

// Add assignment:
class operators::AddAssignment : public operators::BinaryOperator
{
  public:
  AddAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~AddAssignment();
};

// Subtract assignment:
class operators::SubtractAssignment : public operators::BinaryOperator
{
  public:
  SubtractAssignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~SubtractAssignment();
};

// Assignemnt
class operators::Assignment : public operators::BinaryOperator
{
  public:
  Assignment(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Assignment();
};

#endif // ASIGNMENT_H
