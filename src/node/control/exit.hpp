#ifndef EXIT_H
#define EXIT_H

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Exit : public Node {
private:
  NodePtr m_expr;

  public:
  Exit(NodePtr&& t_expr);

  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Exit() = default;
};
} // namespace nodes::control

#endif // EXIT_H
