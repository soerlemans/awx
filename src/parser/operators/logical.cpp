#include "logical.hpp"

using namespace operators;


// Not:
Not::Not(StatementPointer&& t_left)
  : UnaryOperator{StatementType::NOT, Precedence::UnaryPrefix,
                  std::forward<StatementPointer>(t_left)}
{}

auto Not::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Not::~Not()
{}

// And:
And::And(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{StatementType::AND, Precedence::LogicalAnd,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto And::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

And::~And()
{}

// Or:
Or::Or(StatementPointer&& t_left, StatementPointer&& t_right)
  : BinaryOperator{StatementType::OR, Precedence::LogicalOr,
                   Associativity::LEFT, std::forward<StatementPointer>(t_left),
                   std::forward<StatementPointer>(t_right)}
{}

auto Or::accept([[maybe_unused]] StatementVisitor t_visitor) -> void
{
  //
}

Or::~Or()
{}
