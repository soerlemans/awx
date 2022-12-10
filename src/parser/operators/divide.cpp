#include "divide.hpp"

using namespace operators;


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
