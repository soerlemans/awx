#ifndef AST_H
#define AST_H

#include "../types.hpp"

#include "statement/statement.hpp"


// The Abstract Syntax Tree management class
class Ast {
private:
  StatementPointer m_root;
  StatementPointer m_current;

public:

};

#endif // AST_H
