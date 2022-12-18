#include "binary_operator.hpp"

using namespace operators;

BinaryOperator::BinaryOperator(StatementType t_stmnttype,
                               Precedence t_precedence,
                               Associativity t_associativity,
                               StatementPointer&& t_left,
                               StatementPointer&& t_right)
  : UnaryOperator{t_stmnttype, t_precedence,
                  std::forward<StatementPointer>(t_left)},
    m_associativity{t_associativity},
    m_right{std::forward<StatementPointer>(t_right)}
{}

auto BinaryOperator::right() -> StatementPointer&
{
  return m_right;
}

BinaryOperator::~BinaryOperator()
{}
