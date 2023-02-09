#ifndef IF_H
#define IF_H

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class If : public Node {
  private:
  NodePtr m_condition;
  NodePtr m_then;
  NodePtr m_else;

  public:
  If(NodePtr&& t_condition, NodePtr&& t_then);
  If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~If() override = default;
};
} // namespace nodes::control

#endif // IF_H
