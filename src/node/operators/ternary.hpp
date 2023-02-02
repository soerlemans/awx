#ifndef TERNARY_H
#define TERNARY_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
class Ternary : public BinaryOperator {
  protected:
  NodePtr m_else;

  public:
  explicit Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else);

  auto third() -> NodePtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Ternary();
};
} // namespace nodes::operators

#endif // TERNARY_H
