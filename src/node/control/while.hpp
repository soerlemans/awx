#ifndef WHILE_HPP
#define WHILE_HPP

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

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~While() override = default;
};
} // namespace node::control

#endif // WHILE_HPP
