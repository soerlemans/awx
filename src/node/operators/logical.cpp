#include "logical.hpp"


using namespace node::operators;

// Not:
Not::Not(NodePtr&& t_left)
  : UnaryOperator{Precedence::UNARY_PREFIX, std::forward<NodePtr>(t_left)}
{}

auto Not::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_AND, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

auto And::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_OR, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

auto Or::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
