#ifndef NODES_HPP
#define NODES_HPP

#include <memory>


namespace nodes {
// Abstract base Node class
class Node;

// Specifies List of NodePtr's
class List;

// Most Node types inherit from Expression
class Expression;

// Empty Node that does nothing (intended for empty statements)
class Nil;

} // namespace nodes

// Aliases:
using NodePtr = std::unique_ptr<nodes::Node>;
using NodeListPtr = std::unique_ptr<nodes::List>;

#endif // NODES_HPP
