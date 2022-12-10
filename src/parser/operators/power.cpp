#include "power.hpp"


Power::Power(StatementPointer&& t_left,
                                   StatementPointer&& t_right)
  : BinaryOperator{StatementType::POWER, Precedence::ArithmeticMuDiMo,
                   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Power::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Power::~Power()
{}
