#ifndef AWX_NODE_OPERATORS_INCREMENT_HPP
#define AWX_NODE_OPERATORS_INCREMENT_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Increment : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  auto prefix() const -> bool;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Increment() override = default;
};
} // namespace node::operators

#endif
