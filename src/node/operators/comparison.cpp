#include "comparison.hpp"


using namespace nodes::operators;

Comparison::Comparison(ComparisonOp t_op, NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::COMPARISON, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
{}

auto Comparison::op() const -> ComparisonOp
{
  return m_op;
}

auto Comparison::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

Comparison::~Comparison()
{}
