#include "postfix_decrement.hpp"

using namespace operators;


PostfixDecrement::PostfixDecrement(StatementPointer&& t_left)
:UnaryOperator{StatementType::POSTFIX_DECREMENT, Precedence::PostfixIncDec,
				std::forward<StatementPointer>(t_left)}
{}

auto PostfixDecrement::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PostfixDecrement::~PostfixDecrement()
{}
