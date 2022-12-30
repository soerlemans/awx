#include "trinary_operator.hpp"
#include <utility>


using namespace operators;

// Power assignment:
TrinaryOperator::TrinaryOperator(Precedence t_precedence,
                                 Associativity t_associativity,
                                 NodePtr&& t_left, NodePtr&& t_middle,
                                 NodePtr&& t_right)
  : BinaryOperator{Precedence::Conditional, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_middle)},
    m_third{std::forward<NodePtr>(t_right)}
{
}

TrinaryOperator::~TrinaryOperator()
{
}
