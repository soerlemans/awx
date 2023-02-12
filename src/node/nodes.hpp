#ifndef NODES_H
#define NODES_H

#include <memory>

// Contains all classes properly namespaced
namespace nodes {
// Abstract base Node class
class Node;

class List;

// Most Node types inherit from Expression
class Expression;

} // namespace nodes

// Aliases:
using NodePtr = std::unique_ptr<nodes::Node>;

#endif // NODES_H
