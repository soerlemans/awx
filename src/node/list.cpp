#include "list.hpp"


using namespace node;

using namespace visitor;

// Methods:
auto List::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
