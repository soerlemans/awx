#ifndef AWX_NODE_CONTROL_CONTINUE_HPP
#define AWX_NODE_CONTROL_CONTINUE_HPP

// Includes
#include "../node_interface.hpp"

// Local Includes:
#include "control.hpp"


namespace node::control {
class Continue : public NodeInterface {
  public:
  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Continue() = default;
};

} // namespace node::control

#endif // AWX_NODE_CONTROL_CONTINUE_HPP
