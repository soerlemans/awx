#ifndef FOR_HPP
#define FOR_HPP

#include "../list.hpp"

#include "control.hpp"


namespace node::control {
class For : public NodeInterface {
  private:
  NodePtr m_init;
  NodePtr m_condition;
  NodePtr m_expr;

  NodeListPtr m_body;

  public:
  For(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
      NodeListPtr&& t_body);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~For() override = default;
};
} // namespace node::control

#endif // FOR_HPP
