#ifndef LOGICAL_H
#define LOGICAL_H

#include "binary_operator.hpp"
#include "operators.hpp"


// Not:
// Pay attention Not is not a BinaryOperator
class operators::Not : public operators::UnaryOperator
{
  public:
  Not(NodePointer&& t_left);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Not();
};

// And:
class operators::And : public operators::BinaryOperator
{
  public:
  And(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~And();
};

// Or:
class operators::Or : public operators::BinaryOperator
{
  public:
  Or(NodePointer&& t_left, NodePointer&& t_right);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Or();
};

#endif // LOGICAL_H
