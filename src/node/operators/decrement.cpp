#include "decrement.hpp"


using namespace node::operators;

Decrement::Decrement(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::POSTFIX_INC_DEC, std::forward<NodePtr>(t_left)},
    m_prefix{t_prefix}
{}

auto Decrement::accept([[maybe_unused]] NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
