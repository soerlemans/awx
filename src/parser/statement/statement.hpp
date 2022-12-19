#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include <type_traits>

#include "../../types.hpp"

#include "statement_visitor.hpp"


// Forward declarations:
class Statement;

// Aliases:
using StatementPointer = std::unique_ptr<Statement>;

// Enum definitions:
enum class StatementType {
  LITERAL,
  VARIABLE,   // Variables are the only allowed LValue
  EXPRESSION,
};

// Abstract Base Statement class:
// A statement could either be a literal or some form of expression
class Statement {
protected:
  StatementType m_statementtype;

public:
  explicit Statement(StatementType t_statementtype);

  auto type() -> StatementType;

  // Needed for the visitor pattern
  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~Statement();
};

#endif // STATEMENT_H
