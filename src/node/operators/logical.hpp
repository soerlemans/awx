#ifndef LOGICAL_H
#define LOGICAL_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
// Not:
// Pay attention Not is not a BinaryOperator unlike the other Logical operators
// Like And and Or
class Not : public UnaryOperator {
  public:
  Not(NodePtr&& t_left);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Not();
};

// And:
class And : public BinaryOperator {
  public:
  And(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void override;

  auto print() const -> void override;

  virtual ~And();
};

// Or:
class Or : public BinaryOperator {
  public:
  Or(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor t_visitor) -> void override;

  auto print() const -> void override;

  virtual ~Or();
};
}; // namespace nodes::operators

#endif // LOGICAL_H
