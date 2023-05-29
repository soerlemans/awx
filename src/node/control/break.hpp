#ifndef AWX_NODE_CONTROL_BREAK_HPP
#define AWX_NODE_CONTROL_BREAK_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Break : public NodeInterface {
  public:
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Break() = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_BREAK_HPP
