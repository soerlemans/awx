#ifndef COMPARISON_H
#define COMPARISON_H

#include "binary_operator.hpp"
#include "operators.hpp"


enum class ComparisonOp {
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,
};

namespace nodes::operators {
class Comparison : public BinaryOperator {
  private:
  ComparisonOp m_op;

  public:
  Comparison(ComparisonOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto op() const -> ComparisonOp;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Comparison() override = default;
};
} // namespace nodes::operators

#endif // COMPARISON_H
