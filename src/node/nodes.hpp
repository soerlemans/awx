#ifndef NODES_H
#define NODES_H

#include <memory>


namespace nodes {
// Abstract base Node class
class Node;

// Specifies List of NodePtr's
class List;

// Most Node types inherit from Expression
class Expression;

} // namespace nodes

// Aliases:
using NodePtr = std::unique_ptr<nodes::Node>;
using NodeListPtr = std::unique_ptr<nodes::List>;

#endif // NODES_H
