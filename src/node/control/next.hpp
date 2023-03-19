#ifndef NEXT_HPP
#define NEXT_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Next : public NodeInterface {
  public:
  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  virtual ~Next() = default;
};
} // namespace node::control

#endif // NEXT_HPP
