#ifndef TERNARY_H
#define TERNARY_H

#include "operators.hpp"
#include "binary_operator.hpp"


class operators::Ternary : public operators::BinaryOperator
{
  protected:
  NodePtr m_third;

  public:
  explicit Ternary(Precedence t_precedence,
                           Associativity t_associativity, NodePtr&& t_left,
                           NodePtr&& t_middle, NodePtr&& t_right);

  auto third() -> NodePtr&;

  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  virtual ~Ternary();
};


#endif // TERNARY_H
