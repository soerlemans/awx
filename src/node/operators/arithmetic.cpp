#include "arithmetic.hpp"

using namespace operators;

Arithmetic::Arithmetic(NodePtr&& t_left, NodePtr&& t_right,
                       ArithmeticOperation t_operation)
  : BinaryOperator{Precedence::ArithmeticMuDiMo, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_operation{t_operation}
{}

auto Arithmetic::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Arithmetic::~Arithmetic()
{}
