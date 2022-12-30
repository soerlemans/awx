#include "comparison.hpp"


// LessThan:
LessThan::LessThan(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto LessThan::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

LessThan::~LessThan()
{
}

// LessThanEqual:
LessThanEqual::LessThanEqual(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto LessThanEqual::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

LessThanEqual::~LessThanEqual()
{
}

// NotEqual:
NotEqual::NotEqual(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto NotEqual::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

NotEqual::~NotEqual()
{
}

// Equal:
Equal::Equal(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto Equal::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

Equal::~Equal()
{
}

// GreaterThan:
GreaterThan::GreaterThan(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto GreaterThan::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

GreaterThan::~GreaterThan()
{
}

// GreaterThanEqual:
GreaterThanEqual::GreaterThanEqual(NodePointer&& t_left, NodePointer&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePointer>(t_left),
                   std::forward<NodePointer>(t_right)}
{
}

auto GreaterThanEqual::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

GreaterThanEqual::~GreaterThanEqual()
{
}
