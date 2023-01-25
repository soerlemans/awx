#ifndef NODE_H
#define NODE_H

#include <memory>
#include <type_traits>

#include "../types.hpp"
#include "../visitor/node_visitor.hpp"

#include "nodes.hpp"


// Aliases:
using NodePtr = std::unique_ptr<nodes::Node>;

// Enum definitions:
enum class NodeType {
  LITERAL,
  ARRAY,
  VARIABLE, // Variables are the only allowed LValue
  NODE_LIST,
  IO,
  CONTROL_STATEMENT,
  EXPRESSION,
};

// Abstract Base Node class:
// A node could either be a literal or some form of expression
class nodes::Node {
  protected:
  NodeType m_nodetype;

  public:
  explicit Node(NodeType t_nodetype);

  Node(Node&& t_node) = default;
  Node(const Node& t_node) = default;

  auto type() -> NodeType;

  // Needed for the visitor pattern
  // TODO: Figure out if there is a way to not have to implement this in every
  // Derived class
  virtual auto accept(NodeVisitor t_visitor) -> void = 0;

  // Needed for printing the AST
  virtual auto print() const -> void = 0;

  virtual ~Node();
};

#endif // NODE_H
