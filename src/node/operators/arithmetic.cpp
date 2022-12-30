#include "arithmetic.hpp"

using namespace operators;

// Power:
Power::Power(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Multiply::Multiply(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Divide::Divide(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Modulo::Modulo(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Add::Add(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Subtract::Subtract(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{
}

auto Subtract::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Subtract::~Subtract()
{
}
