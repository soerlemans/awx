#ifndef AWX_NODE_OPERATORS_TERNARY_HPP
#define AWX_NODE_OPERATORS_TERNARY_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
class Ternary : public BinaryOperator {
  protected:
  NodePtr m_else;

  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else);

  auto third() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Ternary() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_TERNARY_HPP
