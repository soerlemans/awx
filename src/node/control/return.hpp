#ifndef AWX_NODE_CONTROL_RETURN_HPP
#define AWX_NODE_CONTROL_RETURN_HPP

#include "../node_interface.hpp"

#include "control.hpp"


namespace node::control {
class Return : public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  Return(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Return() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_RETURN_HPP
