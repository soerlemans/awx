#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include "node_visitor.hpp"


// Visitor made for printing the AST Node per node
class Print_Visitor : public NodeVisitor {
private:

public:
  Print_Visitor();

  virtual ~Print_Visitor();
};

#endif // PRINT_VISITOR_H
