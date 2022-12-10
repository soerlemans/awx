#include "increment.hpp"

using namespace operators;


// Postfix:
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


// Prefix:
PrefixIncrement::PrefixIncrement(StatementPointer&& t_left)
:UnaryOperator{StatementType::PREFIX_INCREMENT, Precedence::PrefixIncDec,
				std::forward<StatementPointer>(t_left)}
{}

auto PrefixIncrement::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

PrefixIncrement::~PrefixIncrement()
{}
