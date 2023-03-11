#ifndef BREAK_HPP
#define BREAK_HPP

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Break : public NodeInterface {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Break() = default;
};
} // namespace nodes::control

#endif // BREAK_HPP
