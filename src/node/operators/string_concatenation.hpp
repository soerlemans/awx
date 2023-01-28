#ifndef STRING_CONCATENATION_H
#define STRING_CONCATENATION_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
class StringConcatenation : public BinaryOperator {
  private:
  public:
  StringConcatenation(NodePtr&& t_left, NodePtr&& t_right);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~StringConcatenation();
};
}; // namespace nodes::operators

#endif // STRING_CONCATENATION_H
