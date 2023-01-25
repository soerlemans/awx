#ifndef IF_THEN_ELSE_H
#define IF_THEN_ELSE_H

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class IfThenElse : public Node {
  private:
  NodePtr m_then;
  NodePtr m_else;

  public:
  IfThenElse(NodePtr&& t_then, NodePtr&& t_else);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~IfThenElse();
};
}; // namespace nodes::control

#endif // IF_THEN_ELSE_H
