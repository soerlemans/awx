#include "logical.hpp"

using namespace operators;


// Not:
Not::Not(NodePtr&& t_left)
  : UnaryOperator{Precedence::UnaryPrefix, std::forward<NodePtr>(t_left)}
{
}

auto Not::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Not::~Not()
{
}

// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LogicalAnd, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{
}

auto And::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

And::~And()
{
}

// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LogicalOr, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{
}

auto Or::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Or::~Or()
{
}
