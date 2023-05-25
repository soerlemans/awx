#ifndef AWX_NODE_OPERATORS_GROUPING_HPP
#define AWX_NODE_OPERATORS_GROUPING_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Grouping : public UnaryOperator {
  private:
  public:
  Grouping(NodePtr&& t_expr);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Grouping() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_GROUPING_HPP
