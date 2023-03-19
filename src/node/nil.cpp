#include "nil.hpp"


using namespace node;

using namespace visitor;

auto Nil::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
