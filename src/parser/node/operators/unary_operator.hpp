#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "../expression.hpp"

#include "operators.hpp"


class operators::UnaryOperator : public Expression {
protected:
  NodePointer m_first;

public:
  explicit UnaryOperator(Precedence t_precedence, NodePointer&& t_stmnt);

  auto first() -> NodePointer&;

  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  virtual ~UnaryOperator();
};

#endif // UNARY_OPERATOR_H
