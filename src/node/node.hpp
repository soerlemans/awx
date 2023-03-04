#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <type_traits>

#include "../types.hpp"
#include "../visitor/node_visitor.hpp"

#include "nodes.hpp"


namespace nodes {
// Abstract Base Node class:
// A node could either be a literal or some form of expression
class Node {
  public:
  virtual auto accept(NodeVisitor* t_visitor) -> void = 0;

  virtual ~Node() = default;
};
} // namespace nodes

#endif // NODE_HPP
