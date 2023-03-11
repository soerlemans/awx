#ifndef GROUPING_HPP
#define GROUPING_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Grouping : public UnaryOperator {
  private:
  public:
  Grouping(NodePtr&& t_expr);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Grouping() override = default;
};
} // namespace node::operators

#endif // GROUPING_HPP
