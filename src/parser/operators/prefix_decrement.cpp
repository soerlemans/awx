#include "prefix_decrement.hpp"

using namespace operators;


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
