#include "grouping.hpp"


using namespace node::operators;

using namespace visitor;

Grouping::Grouping(NodePtr&& t_expr)
  : UnaryOperator{Precedence::GROUPING, std::forward<NodePtr>(t_expr)}
{}

