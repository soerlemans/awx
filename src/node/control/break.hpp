#ifndef BREAK_HPP
#define BREAK_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Break : public NodeInterface {
  public:
  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  virtual ~Break() = default;
};
} // namespace node::control

#endif // BREAK_HPP
