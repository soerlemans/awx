#ifndef EXIT_HPP
#define EXIT_HPP

#include "../node_interface.hpp"

#include "control.hpp"

namespace node::control {
class Exit : public NodeInterface {
private:
  NodePtr m_expr;

  public:
  Exit(NodePtr&& t_expr);

  auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Exit() = default;
};
} // namespace node::control

#endif // EXIT_HPP
