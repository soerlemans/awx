#include "ere.hpp"


using namespace nodes::operators;

Ere::Ere(EreOp t_op, NodePtr&& t_string, NodePtr&& t_pattern)
  : BinaryOperator{Precedence::ERE, Associativity::NONE,
                   std::forward<NodePtr>(t_string),
                   std::forward<NodePtr>(t_pattern)}
{}

auto Ere::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

Ere::~Ere()
{}
