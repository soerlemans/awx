#include "comparison.hpp"


// LessThan:
LessThan::LessThan(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
LessThanEqual::LessThanEqual(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
NotEqual::NotEqual(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
Equal::Equal(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
GreaterThan::GreaterThan(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
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
GreaterThanEqual::GreaterThanEqual(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::Comparison, Associativity::NONE,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{
}

auto GreaterThanEqual::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

GreaterThanEqual::~GreaterThanEqual()
{
}
