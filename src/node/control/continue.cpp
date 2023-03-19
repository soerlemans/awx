#include "continue.hpp"


using namespace node::control;

using namespace visitor;

auto Continue::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
