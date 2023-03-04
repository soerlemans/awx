#ifndef NODE_HPP
#define NODE_HPP

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
class Node {
  public:
  virtual auto accept(NodeVisitor* t_visitor) -> void = 0;

  virtual ~Node() = default;
};
} // namespace nodes

#endif // NODE_HPP
