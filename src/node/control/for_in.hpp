#ifndef AWX_NODE_CONTROL_FOR_IN_HPP
#define AWX_NODE_CONTROL_FOR_IN_HPP

// Includes:
#include "../list.hpp"

// Local includes:
#include "control.hpp"


namespace node::control {
class ForIn : public NodeInterface {
  private:
  NodePtr m_identifier;
  NodePtr m_array;
  NodeListPtr m_body;

  public:
  ForIn(NodePtr&& t_identifier, NodePtr&& t_array, NodeListPtr&& t_body);

  auto identifier() -> NodePtr&;
  auto array() -> NodePtr&;
  auto body() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~ForIn() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_FOR_IN_HPP
