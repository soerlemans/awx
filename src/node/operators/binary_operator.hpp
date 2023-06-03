#ifndef AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP
#define AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class BinaryOperator : public UnaryOperator {
  private:
  NodePtr m_right;

  public:
  explicit BinaryOperator(NodePtr&& t_left, NodePtr&& t_right);

  auto right() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~BinaryOperator() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP
