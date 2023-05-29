#include "binary_operator.hpp"

using namespace node::operators;

using namespace visitor;


BinaryOperator::BinaryOperator(Precedence t_precedence,
                               Associativity t_associativity, NodePtr&& t_lhs,
                               NodePtr&& t_rhs)
  : UnaryOperator{t_precedence, std::forward<NodePtr>(t_lhs)},
    m_associativity{t_associativity},
    m_right{std::forward<NodePtr>(t_rhs)}
{}

auto BinaryOperator::right() -> NodePtr&
{
  return m_right;
}
