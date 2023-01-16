#ifndef DECREMENT_H
#define DECREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


namespace nodes::operators {
class Decrement : public UnaryOperator {
  private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Decrement();
};
}; // namespace nodes::operators

#endif // DECREMENT_H
