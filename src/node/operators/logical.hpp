#ifndef LOGICAL_H
#define LOGICAL_H

#include "binary_operator.hpp"
#include "operators.hpp"


// Not:
// Pay attention Not is not a BinaryOperator
class operators::Not : public operators::UnaryOperator
{
  public:
  Not(NodePtr&& t_left);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Not();
};

// And:
class operators::And : public operators::BinaryOperator
{
  public:
  And(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void override;

  auto print()const -> void override;

  virtual ~And();
};

// Or:
class operators::Or : public operators::BinaryOperator
{
  public:
  Or(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void override;

  auto print()const -> void override;

  virtual ~Or();
};

#endif // LOGICAL_H
