#include "increment.hpp"

using namespace operators;


// Postfix:
PostfixIncrement::PostfixIncrement(StatementPointer&& t_left)
  : UnaryOperator{Precedence::PostfixIncDec,
                  std::forward<StatementPointer>(t_left)}
{}

auto PostfixIncrement::accept([[maybe_unused]] StatementVisitor t_visitor)
  -> void
{
  //
}

PostfixIncrement::~PostfixIncrement()
{}


// Prefix:
PrefixIncrement::PrefixIncrement(StatementPointer&& t_left)
  : UnaryOperator{Precedence::PrefixIncDec,
                  std::forward<StatementPointer>(t_left)}
{}

auto PrefixIncrement::accept([[maybe_unused]] StatementVisitor t_visitor)
  -> void
{
  //
}

PrefixIncrement::~PrefixIncrement()
{}
