#include "special_pattern.hpp"


using namespace node::recipes;

SpecialPattern::SpecialPattern(SpecialPatternOp t_op): m_op{t_op}
{}

auto SpecialPattern::op() const -> SpecialPatternOp
{
  return m_op;
}
auto SpecialPattern::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
