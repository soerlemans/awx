#ifndef STATEMENT_VISITOR_H
#define STATEMENT_VISITOR_H

#include "operators/operators.hpp"


// Implementation of the Visitor design pattern for Statements
// This creates a recursive dependency on the different kind of statements
// So all statements need to be forward declared in this header
class StatementVisitor {
private:
public:
  auto visit() -> void;
};

#endif // STATEMENT_VISITOR_H
