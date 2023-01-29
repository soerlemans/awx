#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "../expression.hpp"

#include "operators.hpp"

namespace nodes {
class operators::UnaryOperator : public Expression {
  protected:
  NodePtr m_first;

  public:
  explicit UnaryOperator(Precedence t_precedence, NodePtr&& t_stmnt);

  auto first() -> NodePtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void = 0;

  virtual ~UnaryOperator();
};
}; // namespace nodes

#endif // UNARY_OPERATOR_H
