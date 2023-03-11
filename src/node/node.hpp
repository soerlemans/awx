#ifndef NODE_INTERFACE_HPP
#define NODE_INTERFACE_HPP

// STL Includes:
#include <memory>
#include <type_traits>

// Includes:
#include "../types.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "nodes.hpp"


// TODO: All classes can be generated with macros, we just need the structure
// the rest can be handled by the Visitor pattern
namespace nodes {
/*! Abstract Base Node class:
 * A node could either be a literal or some form of expression
 */
class NodeInterface {
  public:
  virtual auto accept(NodeVisitor* t_visitor) -> void = 0;

  virtual ~NodeInterface() = default;
};
} // namespace nodes

#endif // NODE_INTERFACE_HPP
