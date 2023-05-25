#ifndef AWX_NODE_CONTROL_WHILE_HPP
#define AWX_NODE_CONTROL_WHILE_HPP

#include "../list.hpp"

#include "control.hpp"


namespace node::control {
class While : public NodeInterface {
  private:
  NodePtr m_condition;
  NodeListPtr m_body;

  public:
  While(NodePtr&& t_condition, NodeListPtr&& t_body);

  auto condition() -> NodePtr&;
  auto body() -> NodeListPtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~While() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_WHILE_HPP
