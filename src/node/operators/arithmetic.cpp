#include "arithmetic.hpp"

using namespace operators;

// Power:
Power::Power(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::RIGHT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Power::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Power::~Power()
{
}

// Multiply:
Multiply::Multiply(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Multiply::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Multiply::~Multiply()
{
}

// Divide:
Divide::Divide(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Divide::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Divide::~Divide()
{
}

// Modulo:
Modulo::Modulo(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Modulo::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Modulo::~Modulo()
{
}

// Add:
Add::Add(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Add::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Add::~Add()
{
}

// Subtract:
Subtract::Subtract(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Subtract::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Subtract::~Subtract()
{
}
