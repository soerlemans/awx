#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "operators.hpp"
#include "binary_operator.hpp"


// Power assignment:
class operators::PowerAssignment : public operators::BinaryOperator {
public:
  PowerAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~PowerAssignment();
};

// Multiply assignment:
class operators::MultiplyAssignment : public operators::BinaryOperator {
public:
  MultiplyAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~MultiplyAssignment();
};

// Divide assignemnt:
class operators::DivideAssignment : public operators::BinaryOperator {
public:
  DivideAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~DivideAssignment();
};

// Modulo assignment:
class operators::ModuloAssignment : public operators::BinaryOperator {
public:
  ModuloAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~ModuloAssignment();
};

// Add assignment:
class operators::AddAssignment : public operators::BinaryOperator {
public:
  AddAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~AddAssignment();
};

// Subtract assignment:
class operators::SubtractAssignment : public operators::BinaryOperator {
public:
  SubtractAssignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~SubtractAssignment();
};

// Assignemnt
class operators::Assignment : public operators::BinaryOperator {
public:
  Assignment(StatementPointer&& t_left, StatementPointer&& t_right);

  auto accept(StatementVisitor t_visitor) -> void;

  virtual ~Assignment();
};

#endif // ASIGNMENT_H
