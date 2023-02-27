#include "next.hpp"


using namespace nodes::control;

auto Next::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

