#include "increment.hpp"


using namespace nodes::operators;

// Postfix:
Increment::Increment(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::POSTFIX_INC_DEC, std::forward<NodePtr>(t_left)}, m_prefix{t_prefix}
{
}

auto Increment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto Increment::print() const -> void
{}

Increment::~Increment()
{
}
