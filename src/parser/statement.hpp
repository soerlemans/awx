#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include <type_traits>

#include "statement_visitor.hpp"
#include "statement_type.hpp"


// Forward declarations:
class Statement;

// Aliases:
using StatementPointer = std::unique_ptr<Statement>;

// Abstract Base Statement class:
// A statement could either be a literal or some form of expression
class Statement {
protected:
  StatementType m_stmnttype;

public:
  explicit Statement(StatementType t_stmnttype);

  auto type() -> StatementType;

  // Needed for the visitor pattern
  virtual auto accept(StatementVisitor t_visitor) -> void = 0;

  virtual ~Statement();
};

#endif // STATEMENT_H
