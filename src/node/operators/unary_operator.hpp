#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "../expression.hpp"

#include "operators.hpp"

namespace nodes {
class operators::UnaryOperator : public Expression {
  protected:
  NodePtr m_first;

  public:
  explicit UnaryOperator(Precedence t_precedence, NodePtr&& t_first);

  auto first() -> NodePtr&;

  auto accept(NodeVisitor* t_visitor) -> void override = 0;

  ~UnaryOperator() override = default;
};
} // namespace nodes

#endif // UNARY_OPERATOR_H
