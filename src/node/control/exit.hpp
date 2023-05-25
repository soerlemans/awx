#ifndef AWX_NODE_CONTROL_EXIT_HPP
#define AWX_NODE_CONTROL_EXIT_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Exit : public NodeInterface {
private:
  NodePtr m_expr;

  public:
  Exit(NodePtr&& t_expr);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  virtual ~Exit() = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_EXIT_HPP
