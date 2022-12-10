#include "arithmetic.hpp"

using namespace operators;

// Power:
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

// Multiply:
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

// Divide:
Divide::Divide(StatementPointer&& t_left,
                               StatementPointer&& t_right)
  : BinaryOperator{StatementType::DIVIDE, Precedence::ArithmeticMuDiMo,
                   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Divide::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Divide::~Divide()
{}

// Add:

// Subtract:
