#ifndef AST_HPP
#define AST_HPP

#include "../types.hpp"

#include "../node/list.hpp"
#include "../node/node.hpp"
#include "../visitor/node_visitor.hpp"


// The Abstract Syntax Tree management class
class Ast {
  private:
  // We use raw pointers for determining where we are in the AST
  // This is fine as it is for traversal purposes
  nodes::NodeInterface* m_root;
  nodes::NodeInterface* m_current;

  nodes::List m_list;

  public:
  Ast() = default;
  Ast(Ast&& t_ast) = default;
  // Ast(const Ast& t_ast) = default;

  auto add(NodePtr&& t_node) -> void;

  auto current() const -> nodes::NodeInterface*;

  virtual ~Ast() = default;
};

#endif // AST_HPP
