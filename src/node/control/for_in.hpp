#ifndef AWX_NODE_CONTROL_FOR_IN_HPP
#define AWX_NODE_CONTROL_FOR_IN_HPP

#include "../list.hpp"

#include "control.hpp"


namespace node::control {
class ForIn : public NodeInterface {
  private:
  NodePtr m_identifier;
  NodePtr m_array;
  NodeListPtr m_body;

  public:
  ForIn(NodePtr&& t_identifier, NodePtr&& t_array, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~ForIn() override = default;
};
} // namespace node::control

#endif // AWX_NODE_CONTROL_FOR_IN_HPP
