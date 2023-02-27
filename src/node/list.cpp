#include "list.hpp"


using namespace nodes;

// Methods:
auto List::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
