#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "operators/operators.hpp"


// Implementation of the Visitor design pattern for Nodes
// This creates a recursive dependency on the different kind of nodes
// So all nodes need to be forward declared in this header
class NodeVisitor {
private:
public:
  auto visit() -> void;
};

#endif // NODE_VISITOR_H
