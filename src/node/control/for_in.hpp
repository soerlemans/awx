#ifndef FOR_IN_HPP
#define FOR_IN_HPP

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

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~ForIn() override = default;
};
} // namespace node::control

#endif // FOR_IN_HPP
