#ifndef AWX_NODE_CONTROL_FOR_HPP
#define AWX_NODE_CONTROL_FOR_HPP

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

  auto init() -> NodePtr&;
  auto condition() -> NodePtr&;
  auto expr() -> NodePtr&;

  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~For() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_FOR_HPP
