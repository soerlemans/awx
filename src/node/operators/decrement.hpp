#ifndef DECREMENT_HPP
#define DECREMENT_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace nodes::operators {
class Decrement : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Decrement() override = default;
};
} // namespace nodes::operators

#endif // DECREMENT_HPP
