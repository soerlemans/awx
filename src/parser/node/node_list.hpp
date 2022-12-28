#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <list>

#include "node.hpp"
#include "expression.hpp"


// TODO: Inherit from std::list itself or shadow std::list functions
// This is a list in the sense of a list of expressions or similar
// Think a list of nodes separated by commas like function arguments
// Or function call separated nodes
class NodeList : public Node {
private:
  std::list<NodePointer> m_list;

public:
  NodeList();
  NodeList(NodeList&& t_ast) = default;

  auto add(NodePointer&& t_node) -> void;

  auto accept(NodeVisitor t_visitor) -> void;
};

#endif // NODE_LIST_H
