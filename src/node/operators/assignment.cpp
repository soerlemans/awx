#include "assignment.hpp"


using namespace operators;

// Power assignment:
PowerAssignment::PowerAssignment(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
MultiplyAssignment::MultiplyAssignment(NodePtr&& t_left,
                                       NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
DivideAssignment::DivideAssignment(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
ModuloAssignment::ModuloAssignment(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}

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
AddAssignment::AddAssignment(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
SubtractAssignment::SubtractAssignment(NodePtr&& t_left,
                                       NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Assignment::Assignment(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{
}

auto Assignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Assignment::~Assignment()
{
}
