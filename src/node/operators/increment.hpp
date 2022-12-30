#ifndef INCREMENT_H
#define INCREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


// Postfix:
class operators::PostfixIncrement : public operators::UnaryOperator
{
  public:
  PostfixIncrement(NodePtr&& t_left);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PostfixIncrement();
};

// Prefix:
class operators::PrefixIncrement : public operators::UnaryOperator
{
  public:
  PrefixIncrement(NodePtr&& t_left);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PrefixIncrement();
};

#endif // INCREMENT_H
