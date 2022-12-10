#include "power_operator.hpp"


PowerOperator::PowerOperator(StatementPointer&& t_left,
                                   StatementPointer&& t_right)
  : BinaryOperator{StatementType::EXPONENTATION, Precedence::ArithmeticMuDiMo,
                   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto PowerOperator::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PowerOperator::~PowerOperator()
{}
