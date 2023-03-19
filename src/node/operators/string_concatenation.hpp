#ifndef STRING_CONCATENATION_HPP
#define STRING_CONCATENATION_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
class StringConcatenation : public BinaryOperator {
  private:
  public:
  StringConcatenation(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~StringConcatenation() override = default;
};
} // namespace node::operators

#endif // STRING_CONCATENATION_HPP
