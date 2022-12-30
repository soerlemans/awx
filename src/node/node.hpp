#ifndef NODE_H
#define NODE_H

#include <memory>
#include <type_traits>

#include "../types.hpp"
#include "../visitor/node_visitor.hpp"


// Forward declarations:
class Node;

// Aliases:
using NodePtr = std::unique_ptr<Node>;

// Enum definitions:
enum class NodeType {
  LITERAL,
  VARIABLE, // Variables are the only allowed LValue
  NODE_LIST,
  EXPRESSION,
};

// Abstract Base Node class:
// A node could either be a literal or some form of expression
class Node
{
  protected:
  NodeType m_nodetype;

  public:
  explicit Node(NodeType t_nodetype);

  Node(Node&& t_node) = default;
  Node(const Node& t_node) = default;

  auto type() -> NodeType;

  // Needed for the visitor pattern
  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  // Needed for printing the AST
  virtual auto print() const -> void = 0;

  virtual ~Node();
};

#endif // NODE_H
