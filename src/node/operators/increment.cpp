#include "increment.hpp"


using namespace node::operators;

// Postfix:
Increment::Increment(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::POSTFIX_INC_DEC, std::forward<NodePtr>(t_left)},
    m_prefix{t_prefix}
{}

auto Increment::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
