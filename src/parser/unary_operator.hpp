#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "statement.hpp"


class UnaryOperator : public Statement {
protected:
  StatementPointer m_left;

public:
  explicit UnaryOperator(StatementType t_stmnttype, StatementPointer&& t_stmnt);

  auto left() const -> Statement;

  virtual ~UnaryOperator();
};

#endif // UNARY_OPERATOR_H
