#ifndef AWX_NODE_OPERATORS_UNARY_OPERATOR_HPP
#define AWX_NODE_OPERATORS_UNARY_OPERATOR_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "operators.hpp"


namespace node {
class operators::UnaryOperator : public NodeInterface {
  private:
  NodePtr m_left;

  public:
  explicit UnaryOperator(NodePtr&& t_left);

  auto left() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~UnaryOperator() override = default;
};
} // namespace node

#endif // AWX_NODE_OPERATORS_UNARY_OPERATOR_HPP
