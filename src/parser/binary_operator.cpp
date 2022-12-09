#include "binary_operator.hpp"

#include <utility>

BinaryOperator::BinaryOperator(StatementType t_stmnttype,
                               StatementPointer&& t_left,
                               StatementPointer&& t_right)
  : UnaryOperator{t_stmnttype, std::forward<StatementPointer>(t_left)},
    m_right{std::forward<StatementPointer>(t_right)}
{}

// auto BinaryOperator::right() const -> Statement
// {
//   return *m_right;
// }

BinaryOperator::~BinaryOperator()
{}
