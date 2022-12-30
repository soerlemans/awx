#include "increment.hpp"

using namespace operators;


// Postfix:
PostfixIncrement::PostfixIncrement(NodePtr&& t_left)
  : UnaryOperator{Precedence::PostfixIncDec, std::forward<NodePtr>(t_left)}
{
}

auto PostfixIncrement::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

PostfixIncrement::~PostfixIncrement()
{
}


// Prefix:
PrefixIncrement::PrefixIncrement(NodePtr&& t_left)
  : UnaryOperator{Precedence::PrefixIncDec, std::forward<NodePtr>(t_left)}
{
}

auto PrefixIncrement::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

PrefixIncrement::~PrefixIncrement()
{
}
