#include "increment.hpp"

using namespace operators;


// Postfix:
Increment::Increment(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::PostfixIncDec, std::forward<NodePtr>(t_left)}, m_prefix{t_prefix}
{
}

auto Increment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Increment::~Increment()
{
}
