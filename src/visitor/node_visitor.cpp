#include "node_visitor.hpp"

// Includes:
#include "../node/node_interface.hpp"


using namespace nodes;

auto NodeVisitor::visit(NodeInterface* t_node) -> void
{
  t_node->accept(this);
}
