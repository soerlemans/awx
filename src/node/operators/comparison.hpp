#ifndef COMPARISON_H
#define COMPARISON_H

#include "binary_operator.hpp"
#include "operators.hpp"

enum class ComparisonOperator {
  LESS_THAN,
  LESS_THAN_EQUAL,

  EQUAL,
  NOT_EQUAL,

  GREATER_THAN,
  GREATER_THAN_EQUAL,
};

class operators::Comparison : public operators::BinaryOperator {
  private:
  ComparisonOperator m_operator;

  public:
  Comparison(NodePtr&& t_left, NodePtr&& t_right,
             ComparisonOperator t_operator);

  auto accept(NodeVisitor t_visitor) -> void;

  virtual ~Comparison();
};

#endif // COMPARISON_H
