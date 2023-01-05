#ifndef INCREMENT_H
#define INCREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::Increment : public operators::UnaryOperator
{
  private:
  bool m_prefix;

  public:
  Increment(NodePtr&& t_left, bool t_prefix);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Increment();
};

#endif
