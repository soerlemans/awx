#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "operators.hpp"
#include "unary_operator.hpp"


enum Associativity : u16 {
  NONE = 0,
  LEFT,
  RIGHT,
};

class operators::BinaryOperator : public operators::UnaryOperator
{
  protected:
  Associativity m_associativity;
  NodePtr m_second;

  public:
  explicit BinaryOperator(Precedence t_precedence,
                          Associativity t_associativity, NodePtr&& t_left,
                          NodePtr&& t_right);

  auto second() -> NodePtr&;

  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  virtual ~BinaryOperator();
};
#endif // BINARY_OPERATOR_H