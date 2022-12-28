#include "increment.hpp"

using namespace operators;


// Postfix:
PostfixIncrement::PostfixIncrement(NodePointer&& t_left)
  : UnaryOperator{Precedence::PostfixIncDec,
                  std::forward<NodePointer>(t_left)}
{}

auto PostfixIncrement::accept([[maybe_unused]] NodeVisitor t_visitor)
  -> void
{
  //
}

PostfixIncrement::~PostfixIncrement()
{}


// Prefix:
PrefixIncrement::PrefixIncrement(NodePointer&& t_left)
  : UnaryOperator{Precedence::PrefixIncDec,
                  std::forward<NodePointer>(t_left)}
{}

auto PrefixIncrement::accept([[maybe_unused]] NodeVisitor t_visitor)
  -> void
{
  //
}

PrefixIncrement::~PrefixIncrement()
{}
