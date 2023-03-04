#ifndef WHILE_HPP
#define WHILE_HPP

#include "../list.hpp"

#include "control.hpp"


namespace nodes::control {
class While : public Node {
  private:
  NodePtr m_condition;
  NodeListPtr m_body;

  public:
  While(NodePtr&& t_condition, NodeListPtr&& t_body);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~While() override = default;
};
} // namespace nodes::control

#endif // WHILE_HPP
