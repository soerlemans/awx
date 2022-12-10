#include "prefix_increment.hpp"


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
