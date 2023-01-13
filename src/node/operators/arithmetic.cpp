#include "arithmetic.hpp"


using namespace operators;

Arithmetic::Arithmetic(ArithmeticOp t_op, NodePtr&& t_left,
                       NodePtr&& t_right)
  // TODO: Fix the selection of the precedence
  : BinaryOperator{Precedence::ARITHMETIC_MU_DI_MO, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
{}

auto Arithmetic::accept(NodeVisitor t_visitor) -> void
{}

auto Arithmetic::print() const -> void
{}

Arithmetic::~Arithmetic()
{}
