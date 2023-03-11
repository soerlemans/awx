#include "next.hpp"


using namespace node::control;

auto Next::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

