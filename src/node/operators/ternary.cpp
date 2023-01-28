#include "ternary.hpp"

#include <utility>


using namespace nodes::operators;

// Power assignment:
Ternary::Ternary(NodePtr&& t_condition, NodePtr&& t_then, NodePtr&& t_else)
  : BinaryOperator{Precedence::TERNARY, Associativity::RIGHT,
                   std::forward<NodePtr>(t_condition),
                   std::forward<NodePtr>(t_then)},
    m_third{std::forward<NodePtr>(t_else)}
{}

auto Ternary::accept(NodeVisitor t_visitor) -> void
{}

auto Ternary::print() const -> void
{}

Ternary::~Ternary()
{}
