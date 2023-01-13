#include "ternary.hpp"

#include <utility>


using namespace operators;

// Power assignment:
Ternary::Ternary(Precedence t_precedence,
                                 Associativity t_associativity,
                                 NodePtr&& t_left, NodePtr&& t_middle,
                                 NodePtr&& t_right)
  : BinaryOperator{Precedence::TERNARY, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_middle)},
    m_third{std::forward<NodePtr>(t_right)}
{
}

Ternary::~Ternary()
{
}

