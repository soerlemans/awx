#ifndef AWX_NODE_OPERATORS_DECREMENT_HPP
#define AWX_NODE_OPERATORS_DECREMENT_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Decrement : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Decrement() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_DECREMENT_HPP
