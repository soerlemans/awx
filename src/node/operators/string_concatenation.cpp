#include "string_concatenation.hpp"


using namespace nodes::operators;

StringConcatenation::StringConcatenation(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::STRING_CONCAT, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

auto StringConcatenation::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
