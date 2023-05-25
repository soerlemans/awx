#ifndef AWX_NODE_CONTROL_CONTINUE_HPP
#define AWX_NODE_CONTROL_CONTINUE_HPP

#include "../node_interface.hpp"

#include "control.hpp"


namespace node::control {
class Continue : public NodeInterface {
  public:
  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  virtual ~Continue() = default;
};

} // namespace node::control

#endif // AWX_NODE_CONTROL_CONTINUE_HPP
