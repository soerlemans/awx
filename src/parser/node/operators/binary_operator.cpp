#include "binary_operator.hpp"

using namespace operators;

BinaryOperator::BinaryOperator(Precedence t_precedence,
                               Associativity t_associativity,
                               NodePointer&& t_left,
                               NodePointer&& t_right)
  : UnaryOperator{t_precedence, std::forward<NodePointer>(t_left)},
    m_associativity{t_associativity},
    m_second{std::forward<NodePointer>(t_right)}
{}

auto BinaryOperator::second() -> NodePointer&
{
  return m_second;
}

BinaryOperator::~BinaryOperator()
{}
