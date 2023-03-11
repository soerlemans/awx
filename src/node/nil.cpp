#include "nil.hpp"


using namespace node;

auto Nil::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
