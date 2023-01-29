#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "../node/nodes.hpp"


// Implementation of the Visitor design pattern for Nodes
// This creates a recursive dependency on the different kind of nodes
// So all nodes need to be forward declared in this header
class NodeVisitor {
  private:
  public:
  NodeVisitor();

  virtual auto visit(nodes::List* t_list) -> void = 0;

  virtual auto visit(nodes::Node* t_node) -> void;

  virtual ~NodeVisitor();
};

#endif // NODE_VISITOR_H
