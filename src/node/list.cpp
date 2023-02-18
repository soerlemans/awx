#include "list.hpp"


using namespace nodes;

// Constructor:
List::List(): Node{NodeType::NODE_LIST}
{}

// Methods:
auto List::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
