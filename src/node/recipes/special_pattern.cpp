#include "special_pattern.hpp"


using namespace nodes::recipes;

SpecialPattern::SpecialPattern(SpecialPatternOp t_op)
  : Node{NodeType::RECIPE}, m_op{t_op}
{}

auto SpecialPattern::op() const -> SpecialPatternOp
{
  return m_op;
}
auto SpecialPattern::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

SpecialPattern::~SpecialPattern()
{}
