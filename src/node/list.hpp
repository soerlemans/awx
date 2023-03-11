#ifndef LIST_HPP
#define LIST_HPP

#include <list>
#include <memory>

#include "node_interface.hpp"
#include "node.hpp"


namespace nodes {
// TODO: Inherit from std::list itself or shadow std::list functions
// This is a list in the sense of a list of expressions or similar
// Think a list of nodes separated by commas like function arguments
// Or function call separated nodes
class List : public NodeInterface, public std::list<NodePtr> {
  public:
  List() = default;

  // Must be defaulted, in order to create this function
  List(List&& t_list) = default;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~List() override = default;
};
} // namespace nodes

#endif // LIST_HPP
