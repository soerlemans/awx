#include "list.hpp"


using namespace node;

// Methods:
auto List::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
