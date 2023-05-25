#ifndef AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP
#define AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


enum Associativity : u16 {
  NONE = 0,
  LEFT,
  RIGHT,
};

namespace node::operators {
class BinaryOperator : public UnaryOperator {
  protected:
  Associativity m_associativity;
  NodePtr m_right;

  public:
  explicit BinaryOperator(Precedence t_precedence,
                          Associativity t_associativity, NodePtr&& t_left,
                          NodePtr&& t_right);

  auto right() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override = 0;

  ~BinaryOperator() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_BINARY_OPERATOR_HPP
