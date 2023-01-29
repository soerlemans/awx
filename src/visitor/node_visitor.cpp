#include "node_visitor.hpp"


#include "../node/node.hpp"

#include "../node/operators/decrement.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"

using namespace nodes;

NodeVisitor::NodeVisitor()
{}

auto NodeVisitor::visit(Node* t_node) -> void
{
  t_node->accept(this);
}

NodeVisitor::~NodeVisitor()
{}
