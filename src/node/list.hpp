#ifndef LIST_H
#define LIST_H

#include <list>
#include <memory>

#include "node.hpp"
#include "nodes.hpp"


namespace nodes {

using NodeListPtr = std::unique_ptr<List>;

// TODO: Inherit from std::list itself or shadow std::list functions
// This is a list in the sense of a list of expressions or similar
// Think a list of nodes separated by commas like function arguments
// Or function call separated nodes
class List : public Node, public std::list<NodePtr> {
  public:
  List();
  List(List&& t_ast) = default;

  auto accept(NodeVisitor t_visitor) -> void override;
  auto print() const -> void override;

  virtual ~List();
};
}; // namespace nodes

#endif // LIST_H