#ifndef NEXT_HPP
#define NEXT_HPP

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Next : public NodeInterface {
  public:
  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Next() = default;
};
} // namespace nodes::control

#endif // NEXT_HPP
