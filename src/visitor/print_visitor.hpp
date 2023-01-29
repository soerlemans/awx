#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include <iostream>

#include "node_visitor.hpp"


// Visitor made for printing the AST Node per node
// Has a unique overload for every print
class PrintVisitor : public NodeVisitor {

  public:
  PrintVisitor();

  virtual ~PrintVisitor();
};

#endif // PRINT_VISITOR_H
