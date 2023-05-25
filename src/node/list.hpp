#ifndef AWX_NODE_LIST_HPP
#define AWX_NODE_LIST_HPP

#include <list>
#include <memory>

#include "node.hpp"
#include "node_interface.hpp"


namespace node {
/*! This is a list in the sense of a list of expressions or similar
 * Think a list of nodes separated by commas like function arguments
 * Or function call separated nodes
 */
class List : public NodeInterface, public std::list<NodePtr> {
  public:
  List() = default;

  // Must be defaulted, in order to create this function
  List(List&& t_list) = default;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~List() override = default;
};
} // namespace node

#endif // AWX_NODE_LIST_HPP
