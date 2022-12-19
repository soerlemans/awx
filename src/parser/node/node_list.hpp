#ifndef EXPRESSION_LIST_H
#define EXPRESSION_LIST_H

#include <vector>

#include "node.hpp"
#include "expression.hpp"


// This is a list in the sense of a list of expressions or similar
// Think a list of nodes separated by commas like function arguments
// Or function call separated nodes
class NodeList : public Node {
private:
  std::vector<NodePointer> m_node_list;

public:
  auto add(NodePointer&& t_node) -> void;

  auto accept(NodeVisitor t_visitor) -> void;
};

#endif // EXPRESSION_LIST_H
