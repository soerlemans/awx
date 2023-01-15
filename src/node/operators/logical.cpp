#include "logical.hpp"


using namespace nodes::operators;

// Not:
Not::Not(NodePtr&& t_left)
  : UnaryOperator{Precedence::UNARY_PREFIX, std::forward<NodePtr>(t_left)}
{}

auto Not::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto Not::print() const -> void
{}

Not::~Not()
{}

// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_AND, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

auto And::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto And::print() const -> void
{}

And::~And()
{}

// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_OR, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

auto Or::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto Or::print() const -> void
{}

Or::~Or()
{}
