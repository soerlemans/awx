#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "../node/operators/operators.hpp"
#include "visitor_interface.hpp"


// Implementation of the Visitor design pattern for Nodes
// This creates a recursive dependency on the different kind of nodes
// So all nodes need to be forward declared in this header
class NodeVisitor : public VisitorInterface {
  private:
  public:
  NodeVisitor();

  auto visit() -> void override;

  virtual ~NodeVisitor();
};

#endif // NODE_VISITOR_H
