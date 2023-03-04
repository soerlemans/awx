#ifndef INCREMENT_HPP
#define INCREMENT_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace nodes::operators {
class Increment : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Increment() override = default;
};
} // namespace nodes::operators

#endif
