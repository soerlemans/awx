#ifndef NODES_HPP
#define NODES_HPP

// STL Includes:
#include <memory>


namespace nodes {
// Abstract base Node class
class NodeInterface;

// Specifies List of NodePtr's
class List;

// Most Node types inherit from Expression
class Expression;

// Empty Node that does nothing (intended for empty statements)
class Nil;

} // namespace nodes

// Aliases:
using NodePtr = std::unique_ptr<nodes::NodeInterface>;
using NodeListPtr = std::unique_ptr<nodes::List>;

#endif // NODES_HPP
