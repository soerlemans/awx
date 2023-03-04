#ifndef TERNARY_HPP
#define TERNARY_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
class Ternary : public BinaryOperator {
  protected:
  NodePtr m_else;

  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else);

  auto third() -> NodePtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Ternary() override = default;
};
} // namespace nodes::operators

#endif // TERNARY_HPP
