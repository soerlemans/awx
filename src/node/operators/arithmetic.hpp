#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "operators.hpp"
#include "binary_operator.hpp"


// Power:
class operators::Power : public operators::BinaryOperator {
public:
  Power(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Power();
};

// Multiply:
class operators::Multiply : public operators::BinaryOperator {
public:
  Multiply(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Multiply();
};

// Divide:
class operators::Divide : public operators::BinaryOperator {
public:
  Divide(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Divide();
};

// Modulo:
class operators::Modulo : public operators::BinaryOperator {
public:
  Modulo(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Modulo();
};

// Add:
class operators::Add : public operators::BinaryOperator {
public:
  Add(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Add();
};

// Subtract:
class operators::Subtract : public operators::BinaryOperator {
public:
  Subtract(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Subtract();
};
#endif // ARITHMETIC_H
