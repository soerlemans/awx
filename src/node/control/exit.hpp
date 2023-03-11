#ifndef EXIT_HPP
#define EXIT_HPP

#include "../node.hpp"

#include "control.hpp"

namespace nodes::control {
class Exit : public NodeInterface {
private:
  NodePtr m_expr;

  public:
  Exit(NodePtr&& t_expr);

  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Exit() = default;
};
} // namespace nodes::control

#endif // EXIT_HPP
