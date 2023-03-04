#ifndef STRING_CONCATENATION_HPP
#define STRING_CONCATENATION_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
class StringConcatenation : public BinaryOperator {
  private:
  public:
  StringConcatenation(NodePtr&& t_left, NodePtr&& t_right);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~StringConcatenation() override = default;
};
} // namespace nodes::operators

#endif // STRING_CONCATENATION_HPP
