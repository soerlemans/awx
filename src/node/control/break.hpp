#ifndef BREAK_H
#define BREAK_H

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Break : public Node {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Break() = default;
};
} // namespace nodes::control

#endif // BREAK_H
