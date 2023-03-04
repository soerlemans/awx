#include "nil.hpp"


using namespace nodes;

auto Nil::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
