#ifndef TRINARY_OPERATOR_H
#define TRINARY_OPERATOR_H

#include "binary_operator.hpp"
#include "operators.hpp"

class operators::TrinaryOperator : public operators::BinaryOperator
{
  protected:
  NodePtr m_third;

  public:
  explicit TrinaryOperator(Precedence t_precedence,
                           Associativity t_associativity, NodePtr&& t_left,
                           NodePtr&& t_middle, NodePtr&& t_right);

  auto third() -> NodePtr&;

  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  virtual ~TrinaryOperator();
};

#endif // TRINARY_OPERATOR_H