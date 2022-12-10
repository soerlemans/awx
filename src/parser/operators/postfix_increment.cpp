#include "postfix_increment.hpp"

using namespace operators;


PostfixIncrement::PostfixIncrement(StatementPointer&& t_left)
:UnaryOperator{StatementType::POSTFIX_INCREMENT, Precedence::PostfixIncDec,
				std::forward<StatementPointer>(t_left)}
{}

auto PostfixIncrement::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PostfixIncrement::~PostfixIncrement()
{}
