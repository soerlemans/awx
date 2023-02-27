#include "break.hpp"


using namespace nodes::control;

auto Break::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
