#ifndef IF_H
#define IF_H

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class If : public Node {
  private:
  NodePtr m_predicate;
  NodePtr m_then;
  NodePtr m_else;

  public:
  If(NodePtr&& t_predicate, NodePtr&& t_then, NodePtr&& t_else);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~If();
};
} // namespace nodes::control

#endif // IF_H
