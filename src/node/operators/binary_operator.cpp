#include "binary_operator.hpp"

using namespace nodes::operators;


BinaryOperator::BinaryOperator(Precedence t_precedence,
                               Associativity t_associativity,
                               NodePtr&& t_left, NodePtr&& t_right)
  : UnaryOperator{t_precedence, std::forward<NodePtr>(t_left)},
    m_associativity{t_associativity},
    m_second{std::forward<NodePtr>(t_right)}
{
}

auto BinaryOperator::second() -> NodePtr&
{
  return m_second;
}

BinaryOperator::~BinaryOperator()
{
}
