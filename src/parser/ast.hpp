#ifndef AST_H
#define AST_H

#include "../types.hpp"

#include "../node/node.hpp"
#include "../node/node_list.hpp"
#include "../node/node_visitor.hpp"


// The Abstract Syntax Tree management class
class Ast {
private:
  // We use raw pointers for determining where we are in the AST
  // This is fine as it is for traversal purposes
  Node* m_root;
  Node* m_current;

  NodeList m_list;

  NodeVisitor m_visitor;

public:
  Ast();
  Ast(Ast&& t_ast) = default;
  // Ast(const Ast& t_ast) = default;

  auto add(NodePointer&& t_node) -> void;

  virtual ~Ast();
};

// Exported functions:
auto print_ast(const Ast& t_ast) -> void;

#endif // AST_H
