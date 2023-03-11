#ifndef AST_HPP
#define AST_HPP

#include "../types.hpp"

#include "../node/list.hpp"
#include "../node/node_interface.hpp"
#include "../visitor/node_visitor.hpp"


// The Abstract Syntax Tree management class
class Ast {
  private:
  // We use raw pointers for determining where we are in the AST
  // This is fine as it is for traversal purposes
  node::NodeInterface* m_root;
  node::NodeInterface* m_current;

  node::List m_list;

  public:
  Ast() = default;
  Ast(Ast&& t_ast) = default;
  // Ast(const Ast& t_ast) = default;

  auto add(NodePtr&& t_node) -> void;

  auto current() const -> node::NodeInterface*;

  virtual ~Ast() = default;
};

#endif // AST_HPP
