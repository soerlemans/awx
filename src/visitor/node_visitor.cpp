#include "node_visitor.hpp"

#include "../node/operators/decrement.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"


NodeVisitor::NodeVisitor()
{}

auto NodeVisitor::visit() -> void
{}

NodeVisitor::~NodeVisitor()
{}
