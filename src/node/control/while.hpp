#ifndef WHILE_H
#define WHILE_H

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class While : public Node {
  private:
  NodePtr m_condition;
  NodePtr m_body;

  public:
  While(NodePtr&& t_condition, NodePtr&& t_body);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~While();
};
} // namespace nodes::control

#endif // WHILE_H
