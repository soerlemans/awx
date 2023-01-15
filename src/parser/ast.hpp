#ifndef AST_H
#define AST_H

#include "../types.hpp"

#include "../node/node.hpp"
#include "../node/list.hpp"
#include "../visitor/node_visitor.hpp"


// The Abstract Syntax Tree management class
class Ast
{
  private:
  // We use raw pointers for determining where we are in the AST
  // This is fine as it is for traversal purposes
  nodes::Node* m_root;
  nodes::Node* m_current;

  nodes::List m_list;

  public:
  Ast();
  Ast(Ast&& t_ast) = default;
  // Ast(const Ast& t_ast) = default;

  auto add(NodePtr&& t_node) -> void;

  virtual ~Ast();
};

// Exported functions:
auto print_ast(const Ast& t_ast) -> void;

#endif // AST_H
