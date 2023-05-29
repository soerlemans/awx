#ifndef AWX_NODE_CONTROL_DO_WHILE_HPP
#define AWX_NODE_CONTROL_DO_WHILE_HPP

// Includes:
#include "../list.hpp"

// Local Includes:
#include "control.hpp"


namespace node::control {
class DoWhile : public NodeInterface {
  private:
  NodePtr m_condition;
  NodeListPtr m_body;

  public:
  DoWhile(NodePtr&& t_condition, NodeListPtr&& t_body);

  auto condition() -> NodePtr&;
  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~DoWhile() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_DO_WHILE_HPP
