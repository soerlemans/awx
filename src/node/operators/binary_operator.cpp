#include "binary_operator.hpp"

using namespace node::operators;

using namespace visitor;


BinaryOperator::BinaryOperator(Precedence t_precedence,
                               Associativity t_associativity, NodePtr&& t_left,
                               NodePtr&& t_right)
  : UnaryOperator{t_precedence, std::forward<NodePtr>(t_left)},
    m_associativity{t_associativity},
    m_right{std::forward<NodePtr>(t_right)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
