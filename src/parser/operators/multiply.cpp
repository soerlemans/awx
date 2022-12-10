#include "multiply.hpp"


Multiply::Multiply(StatementPointer&& t_left,
                                   StatementPointer&& t_right)
:BinaryOperator{StatementType::MULTIPLY, Precedence::ArithmeticMuDiMo,
				std::forward<StatementPointer>(t_left),
				std::forward<StatementPointer>(t_right)}
{}

auto Multiply::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Multiply::~Multiply()
{}
