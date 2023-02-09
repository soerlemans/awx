#ifndef GROUPING_H
#define GROUPING_H

#include "operators.hpp"
#include "unary_operator.hpp"


namespace nodes::operators {
class Grouping : public UnaryOperator {
  private:
  public:
  Grouping(NodePtr&& t_expr);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Grouping() override = default;
};
} // namespace nodess::operators

#endif // GROUPING_H
