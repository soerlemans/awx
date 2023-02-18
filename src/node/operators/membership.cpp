#include "membership.hpp"


using namespace nodes::operators;

Membership::Membership(NodePtr&& t_lhs, const std::string& t_name)
  : UnaryOperator{Precedence::MEMBERSHIP, std::forward<NodePtr>(t_lhs)},
    m_name{t_name}
{}

auto Membership::name() const -> std::string_view
{
  return {m_name};
}

auto Membership::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
