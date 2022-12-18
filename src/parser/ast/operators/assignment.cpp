#include "assignment.hpp"


using namespace operators;

// Power assignment:
PowerAssignment::PowerAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{StatementType::POWER_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto PowerAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PowerAssignment::~PowerAssignment()
{}

// Multiply assignment:
MultiplyAssignment::MultiplyAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{StatementType::MULTIPLY_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto MultiplyAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

MultiplyAssignment::~MultiplyAssignment()
{}

// Divide assignment:
DivideAssignment::DivideAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{StatementType::DIVIDE_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto DivideAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

DivideAssignment::~DivideAssignment()
{}

// Modulo assignment:
ModuloAssignment::ModuloAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
    : BinaryOperator{StatementType::MODULO_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}

{}

auto ModuloAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

ModuloAssignment::~ModuloAssignment()
{}

// Add assignment:
AddAssignment::AddAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
    : BinaryOperator{StatementType::ADD_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto AddAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

AddAssignment::~AddAssignment()
{}

// Subtract assignment:
SubtractAssignment::SubtractAssignment(StatementPointer&& t_left, StatementPointer&& t_right)
    : BinaryOperator{StatementType::SUBTRACT_ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto SubtractAssignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

SubtractAssignment::~SubtractAssignment()
{}

// Assignment:
Assignment::Assignment(StatementPointer&& t_left, StatementPointer&& t_right)
    : BinaryOperator{StatementType::ASSIGNMENT,
				   Precedence::Assignment,
                   Associativity::RIGHT,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Assignment::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Assignment::~Assignment()
{}
