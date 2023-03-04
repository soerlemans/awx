#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
// Not:
// Pay attention Not is not a BinaryOperator unlike the other Logical operators
// Like And and Or
class Not : public UnaryOperator {
  public:
  Not(NodePtr&& t_left);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Not() override = default;
};

// TODO: Create one class for And and Or
// And:
class And : public BinaryOperator {
  public:
  And(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~And() override = default;
};

// Or:
class Or : public BinaryOperator {
  public:
  Or(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Or() override = default;
};
} // namespace nodes::operators

#endif // LOGICAL_HPP
