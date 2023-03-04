#ifndef CONTINUE_HPP
#define CONTINUE_HPP

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class Continue : public Node {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Continue() = default;
};

} // namespace nodes::control

#endif // CONTINUE_HPP
