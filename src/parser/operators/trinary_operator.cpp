#include "trinary_operator.hpp"
#include <utility>


using namespace operators;

// Power assignment:
TrinaryOperator::TrinaryOperator(StatementType t_stmnttype,
                                 Precedence t_precedence,
                                 Associativity t_associativity,
                                 StatementPointer&& t_left,
                                 StatementPointer&& t_middle,
                                 StatementPointer&& t_right)
  : BinaryOperator{StatementType::POWER_ASSIGNMENT, Precedence::Assignment,
                   Associativity::RIGHT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_middle)},
    m_third{std::forward<StatementPointer>(t_right)}
{}

TrinaryOperator::~TrinaryOperator()
{}
