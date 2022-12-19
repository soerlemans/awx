#include "arithmetic.hpp"

using namespace operators;

// Power:
Power::Power(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::RIGHT,
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
Multiply::Multiply(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
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
Divide::Divide(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Divide::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Divide::~Divide()
{}

// Modulo:
Modulo::Modulo(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Modulo::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Modulo::~Modulo()
{}

// Add:
Add::Add(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Add::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Add::~Add()
{}

// Subtract:
Subtract::Subtract(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Subtract::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Subtract::~Subtract()
{}
