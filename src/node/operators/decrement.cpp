#include "decrement.hpp"

using namespace operators;


Decrement::Decrement(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::PostfixIncDec, std::forward<NodePtr>(t_left)},
    m_prefix{t_prefix}
{
}

auto Decrement::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto Decrement::print() const -> void
{}

Decrement::~Decrement()
{
}
