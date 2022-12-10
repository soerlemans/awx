#include "multiply_operator.hpp"


MultiplyOperator::MultiplyOperator(StatementPointer&& t_left,
                                   StatementPointer&& t_right)
:BinaryOperator{StatementType::MULTIPLICATION, Precedence::ArithmeticMuDiMo,
				std::forward<StatementPointer>(t_left),
				std::forward<StatementPointer>(t_right)}
{}

auto MultiplyOperator::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

MultiplyOperator::~MultiplyOperator()
{}
