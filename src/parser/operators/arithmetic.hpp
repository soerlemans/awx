#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "operators.hpp"
#include "binary_operator.hpp"


// Power:
class operators::Power : public operators::BinaryOperator {
public:
  Power(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Power();
};

// Multiply:
class operators::Multiply : public operators::BinaryOperator {
public:
  Multiply(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Multiply();
};

// Divide:
class operators::Divide : public operators::BinaryOperator {
public:
  Divide(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Divide();
};

#endif // ARITHMETIC_H
