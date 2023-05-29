#ifndef AWX_NODE_NODE_INTERFACE_HPP
#define AWX_NODE_NODE_INTERFACE_HPP

// STL Includes:
#include <memory>
#include <type_traits>

// Includes:
#include "../types.hpp"
#include "../visitor/node_visitor.hpp"
#include "../visitor/visitable.hpp"

// Local Includes:
#include "node.hpp"


// TODO: All classes can be generated with macros, we just need the structure
// the rest can be handled by the Visitor pattern
namespace node {
/*! Abstract Base Node class:
 * A node could either be a literal or some form of expression
 */
class NodeInterface : public visitor::Visitable<visitor::NodeVisitor> {
  public:
  virtual auto accept(visitor::NodeVisitor* t_visitor) -> void = 0;

  virtual ~NodeInterface() = default;
};
} // namespace node

#endif // AWX_NODE_NODE_INTERFACE_HPP
