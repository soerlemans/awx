#include "logical.hpp"


using namespace node::operators;

using namespace visitor;

// Not:
Not::Not(NodePtr&& t_left)
  : UnaryOperator{Precedence::UNARY_PREFIX, std::forward<NodePtr>(t_left)}
{}


// And:
And::And(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_AND, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}


// Or:
Or::Or(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{Precedence::LOGICAL_OR, Associativity::LEFT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}

