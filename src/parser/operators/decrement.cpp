#include "decrement.hpp"

using namespace operators;


// Postfix:
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

// Prefix:
PrefixDecrement::PrefixDecrement(StatementPointer&& t_left)
:UnaryOperator{StatementType::PREFIX_DECREMENT, Precedence::PrefixIncDec,
				std::forward<StatementPointer>(t_left)}
{}

auto PrefixDecrement::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PrefixDecrement::~PrefixDecrement()
{}
