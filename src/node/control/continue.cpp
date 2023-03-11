#include "continue.hpp"


using namespace node::control;

auto Continue::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
