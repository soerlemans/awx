#ifndef AST_H
#define AST_H

#include "../types.hpp"

#include "node/node.hpp"
#include "node/node_list.hpp"


// The Abstract Syntax Tree management class
class Ast {
private:
  NodePointer m_root;
  NodePointer m_current;

  NodeList m_list;

public:
  Ast();
  // Must define a copy constructor as unique_ptr's dont have any
  // Ast(const Ast& t_ast) = default;

  // add

  virtual ~Ast();
};

#endif // AST_H
