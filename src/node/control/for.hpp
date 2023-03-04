#ifndef FOR_HPP
#define FOR_HPP

#include "../list.hpp"

#include "control.hpp"


namespace nodes::control {
class For : public Node {
  private:
  NodePtr m_init;
  NodePtr m_condition;
  NodePtr m_expr;

  NodeListPtr m_body;

  public:
  For(NodePtr&& t_init, NodePtr&& t_condition, NodePtr&& t_expr,
      NodeListPtr&& t_body);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~For() override = default;
};
} // namespace nodes::control

#endif // FOR_HPP
