#ifndef AWX_NODE_OPERATORS_COMPARISON_HPP
#define AWX_NODE_OPERATORS_COMPARISON_HPP

// Local Includes:
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

namespace node::operators {
class Comparison : public BinaryOperator {
  private:
  ComparisonOp m_op;

  public:
  Comparison(ComparisonOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto op() const -> ComparisonOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Comparison() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_COMPARISON_HPP
