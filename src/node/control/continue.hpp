#ifndef CONTINUE_HPP
#define CONTINUE_HPP

#include "../node_interface.hpp"

#include "control.hpp"


namespace nodes::control {
class Continue : public NodeInterface {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Continue() = default;
};

} // namespace nodes::control

#endif // CONTINUE_HPP
