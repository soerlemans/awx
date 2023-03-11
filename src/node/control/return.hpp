#ifndef RETURN_HPP
#define RETURN_HPP

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class Return : public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  Return(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Return() override = default;
};
} // namespace nodes::control

#endif // RETURN_HPP
