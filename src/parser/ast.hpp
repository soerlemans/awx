#ifndef AST_H
#define AST_H

#include "../types.hpp"

#include "statement.hpp"


// The Abstract Syntax Tree management class
class Ast {
private:
  StatementPointer m_root;
  StatementPointer m_current;

public:
  Ast() = default;
  virtual ~Ast() = default;
};

#endif // AST_H
