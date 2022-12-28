#include "decrement.hpp"

using namespace operators;


// Postfix:
PostfixDecrement::PostfixDecrement(NodePointer&& t_left)
  : UnaryOperator{Precedence::PostfixIncDec,
                  std::forward<NodePointer>(t_left)}
{}

auto PostfixDecrement::accept([[maybe_unused]] NodeVisitor t_visitor)
  -> void
{
  //
}

PostfixDecrement::~PostfixDecrement()
{}

// Prefix:
PrefixDecrement::PrefixDecrement(NodePointer&& t_left)
  : UnaryOperator{Precedence::PrefixIncDec,
                  std::forward<NodePointer>(t_left)}
{}

auto PrefixDecrement::accept([[maybe_unused]] NodeVisitor t_visitor)
  -> void
{
  //
}

PrefixDecrement::~PrefixDecrement()
{}
