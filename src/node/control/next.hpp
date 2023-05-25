#ifndef AWX_NODE_CONTROL_NEXT_HPP
#define AWX_NODE_CONTROL_NEXT_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Next : public NodeInterface {
  public:
  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  virtual ~Next() = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_NEXT_HPP
