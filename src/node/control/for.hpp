#ifndef FOR_H
#define FOR_H

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class For : public Node {
  private:
  NodePtr m_condition;
  NodePtr m_body;

  public:
  For(NodePtr&& t_condition, NodePtr&& t_body);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~For();
};
} // namespace nodes::control

#endif // FOR_H
