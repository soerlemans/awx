#include "trinary_operator.hpp"
#include <utility>


using namespace operators;

// Power assignment:
TrinaryOperator::TrinaryOperator(Precedence t_precedence,
                                 Associativity t_associativity,
                                 NodePointer&& t_left, NodePointer&& t_middle,
                                 NodePointer&& t_right)
  : BinaryOperator{Precedence::Conditional, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_middle)},
    m_third{std::forward<NodePointer>(t_right)}
{
}

TrinaryOperator::~TrinaryOperator()
{
}
