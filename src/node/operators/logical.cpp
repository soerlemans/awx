#include "logical.hpp"

using namespace operators;


// Not:
Not::Not(NodePointer&& t_left)
  : UnaryOperator{Precedence::UnaryPrefix,
                  std::forward<NodePointer>(t_left)}
{}

auto Not::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Not::~Not()
{}

// And:
And::And(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::LogicalAnd, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{}

auto And::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

And::~And()
{}

// Or:
Or::Or(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::LogicalOr, Associativity::LEFT,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{}

auto Or::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Or::~Or()
{}
