#include "unary_operator.hpp"


UnaryOperator::UnaryOperator(StatementType t_stmnttype, StatementPointer&& t_stmnt)
  :Statement{t_stmnttype}, m_left{std::forward<StatementPointer>(t_stmnt)}
{}

// auto UnaryOperator::left() const -> Statement
// {
//   return *m_left;
// }

UnaryOperator::~UnaryOperator()
{}
