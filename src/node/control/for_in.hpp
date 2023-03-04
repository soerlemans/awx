#ifndef FOR_IN_HPP
#define FOR_IN_HPP

#include "../list.hpp"

#include "control.hpp"


namespace nodes::control {
class ForIn : public Node {
  private:
  NodePtr m_condition;
  NodeListPtr m_body;

  public:
  ForIn(NodePtr&& t_condition, NodeListPtr&& t_body);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~ForIn() override = default;
};
} // namespace nodes::control

#endif // FOR_IN_HPP
