#ifndef DECREMENT_H
#define DECREMENT_H

#include "operators.hpp"
#include "unary_operator.hpp"


// Postfix:
class operators::PostfixDecrement: public operators::UnaryOperator {
public:
  PostfixDecrement(NodePointer&& t_left);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PostfixDecrement();
};

// Prefix:
class operators::PrefixDecrement: public operators::UnaryOperator {
public:
  PrefixDecrement(NodePointer&& t_left);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~PrefixDecrement();
};

#endif // DECREMENT_H
