#include "divide_operator.hpp"


DivideOperator::DivideOperator(StatementPointer&& t_left,
                                   StatementPointer&& t_right)
  : BinaryOperator{StatementType::EXPONENTATION, Precedence::ArithmeticMuDiMo,
                   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto DivideOperator::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

DivideOperator::~DivideOperator()
{}
