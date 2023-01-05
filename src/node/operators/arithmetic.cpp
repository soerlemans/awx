#include "arithmetic.hpp"

using namespace operators;

Arithmetic::Arithmetic(ArithmeticOperation t_operation, NodePtr&& t_left,
                       NodePtr&& t_right)
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
