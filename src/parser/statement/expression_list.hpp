#ifndef EXPRESSION_LIST_H
#define EXPRESSION_LIST_H

#include <vector>

#include "statement.hpp"
#include "expression.hpp"


class ExpressionList : public Statement {
private:
  std::vector<StatementPointer> m_expr_list;

public:
  virtual auto add(StatementPointer&& t_statement) -> void;
};

#endif // EXPRESSION_LIST_H
