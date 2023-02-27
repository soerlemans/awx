#ifndef NEXT_H
#define NEXT_H

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Next : public Node {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Next() = default;
};
} // namespace nodes::control

#endif // NEXT_H
