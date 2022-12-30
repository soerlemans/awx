#include "decrement.hpp"

using namespace operators;


// Postfix:
PostfixDecrement::PostfixDecrement(NodePtr&& t_left)
  : UnaryOperator{Precedence::PostfixIncDec, std::forward<NodePtr>(t_left)}
{
}

auto PostfixDecrement::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

PostfixDecrement::~PostfixDecrement()
{
}

// Prefix:
PrefixDecrement::PrefixDecrement(NodePtr&& t_left)
  : UnaryOperator{Precedence::PrefixIncDec, std::forward<NodePtr>(t_left)}
{
}

auto PrefixDecrement::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

PrefixDecrement::~PrefixDecrement()
{
}
