#include "assignment.hpp"


using namespace operators;

// Power assignment:
PowerAssignment::PowerAssignment(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto PowerAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

PowerAssignment::~PowerAssignment()
{
}

// Multiply assignment:
MultiplyAssignment::MultiplyAssignment(NodePointer&& t_left,
                                       NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto MultiplyAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

MultiplyAssignment::~MultiplyAssignment()
{
}

// Divide assignment:
DivideAssignment::DivideAssignment(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto DivideAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

DivideAssignment::~DivideAssignment()
{
}

// Modulo assignment:
ModuloAssignment::ModuloAssignment(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}

{
}

auto ModuloAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

ModuloAssignment::~ModuloAssignment()
{
}

// Add assignment:
AddAssignment::AddAssignment(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto AddAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

AddAssignment::~AddAssignment()
{
}

// Subtract assignment:
SubtractAssignment::SubtractAssignment(NodePointer&& t_left,
                                       NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto SubtractAssignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

SubtractAssignment::~SubtractAssignment()
{
}

// Assignment:
Assignment::Assignment(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Assignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Assignment::~Assignment()
{
}
