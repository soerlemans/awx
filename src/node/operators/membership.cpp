#include "membership.hpp"


using namespace node::operators;

Membership::Membership(NodePtr&& t_lhs, std::string&& t_name)
  : UnaryOperator{Precedence::MEMBERSHIP, std::forward<NodePtr>(t_lhs)},
    m_name{std::forward<std::string>(t_name)}
{}

auto Membership::name() const -> std::string_view
{
  return {m_name};
}

auto Membership::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}