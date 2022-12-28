#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "operators.hpp"
#include "binary_operator.hpp"


// Power assignment:
class operators::PowerAssignment : public operators::BinaryOperator {
public:
  PowerAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PowerAssignment();
};

// Multiply assignment:
class operators::MultiplyAssignment : public operators::BinaryOperator {
public:
  MultiplyAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~MultiplyAssignment();
};

// Divide assignemnt:
class operators::DivideAssignment : public operators::BinaryOperator {
public:
  DivideAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~DivideAssignment();
};

// Modulo assignment:
class operators::ModuloAssignment : public operators::BinaryOperator {
public:
  ModuloAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~ModuloAssignment();
};

// Add assignment:
class operators::AddAssignment : public operators::BinaryOperator {
public:
  AddAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~AddAssignment();
};

// Subtract assignment:
class operators::SubtractAssignment : public operators::BinaryOperator {
public:
  SubtractAssignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~SubtractAssignment();
};

// Assignemnt
class operators::Assignment : public operators::BinaryOperator {
public:
  Assignment(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Assignment();
};

#endif // ASIGNMENT_H
