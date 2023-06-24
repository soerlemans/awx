#ifndef AWX_NODE_OPERATORS_STRING_CONCATENATION_HPP
#define AWX_NODE_OPERATORS_STRING_CONCATENATION_HPP

// Local Includes;
#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
class StringConcatenation : public BinaryOperator {
  private:
  public:
  StringConcatenation(NodePtr&& t_left, NodePtr&& t_right);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~StringConcatenation() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_STRING_CONCATENATION_HPP
