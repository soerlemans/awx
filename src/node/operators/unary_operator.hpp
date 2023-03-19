#ifndef UNARY_OPERATOR_HPP
#define UNARY_OPERATOR_HPP

#include "../expression.hpp"

#include "operators.hpp"

namespace node {
class operators::UnaryOperator : public Expression {
  protected:
  NodePtr m_left;

  public:
  explicit UnaryOperator(Precedence t_precedence, NodePtr&& t_left);

  auto left() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~UnaryOperator() override = default;
};
} // namespace node

#endif // UNARY_OPERATOR_HPP
