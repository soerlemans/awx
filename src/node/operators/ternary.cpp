#include "ternary.hpp"

#include <utility>


using namespace nodes::operators;

// TODO: Error throw when a nullptr is given as agrg
Ternary::Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else)
  : BinaryOperator{Precedence::TERNARY, Associativity::RIGHT,
                   std::forward<NodePtr>(t_condition),
                   std::forward<NodePtr>(t_then)},
    m_else{std::forward<NodePtr>(t_else)}
{}

auto Ternary::third() -> NodePtr&
{
  return m_else;
}

auto Ternary::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

Ternary::~Ternary()
{}
