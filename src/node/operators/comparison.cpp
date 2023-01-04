#include "comparison.hpp"

using namespace operators;


Comparison::Comparison(NodePtr&& t_left, NodePtr&& t_right,
                                       ComparisonOperator t_operator)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_operator{t_operator}
{}

auto Comparison::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Comparison::~Comparison()
{}
