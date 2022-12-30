#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include <iostream>

#include "../parser/ast.hpp"

#include "visitor_interface.hpp"


// Visitor made for printing the AST Node per node
class PrintVisitor : public VisitorInterface
{
  private:
  Ast& m_ast;

  public:
  PrintVisitor(Ast& t_ast);

  auto visit() -> void override;

  virtual ~PrintVisitor();
};

#endif // PRINT_VISITOR_H
