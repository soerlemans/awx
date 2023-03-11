#ifndef IF_HPP
#define IF_HPP

#include "../node.hpp"

#include "control.hpp"


namespace nodes::control {
class If : public NodeInterface {
  private:
  NodePtr m_condition;
  NodePtr m_then;
  NodePtr m_else;

  public:
  If(NodePtr&& t_condition, NodePtr&& t_then);
  If(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else);

  auto then() -> NodePtr&;
  auto alt() -> NodePtr&; // Alternative is a synonym for else

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~If() override = default;
};
} // namespace nodes::control

#endif // IF_HPP
