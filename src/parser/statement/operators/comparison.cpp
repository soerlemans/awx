#include "comparison.hpp"


// LessThan:
LessThan::LessThan(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto LessThan::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

LessThan::~LessThan()
{}

// LessThanEqual:
LessThanEqual::LessThanEqual(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE,
				   std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto LessThanEqual::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

LessThanEqual::~LessThanEqual()
{}

// NotEqual:
NotEqual::NotEqual(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto NotEqual::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

NotEqual::~NotEqual()
{}

// Equal:
Equal::Equal(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Equal::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Equal::~Equal()
{}

// GreaterThan:
GreaterThan::GreaterThan(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto GreaterThan::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

GreaterThan::~GreaterThan()
{}

// GreaterThanEqual:
GreaterThanEqual::GreaterThanEqual(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{Precedence::Comparison,
                   Associativity::NONE, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto GreaterThanEqual::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

GreaterThanEqual::~GreaterThanEqual()
{}
