#include "special_pattern.hpp"


using namespace node::recipes;

using namespace visitor;

SpecialPattern::SpecialPattern(SpecialPatternOp t_op): m_op{t_op}
{}

auto SpecialPattern::op() const -> SpecialPatternOp
{
  return m_op;
}
