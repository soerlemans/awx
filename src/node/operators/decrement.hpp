#ifndef DECREMENT_H
#define DECREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::Decrement : public operators::UnaryOperator
{
private:
  bool m_prefix;

  public:
  Decrement(NodePtr&& t_left, bool t_prefix);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Decrement();
};


#endif // DECREMENT_H
