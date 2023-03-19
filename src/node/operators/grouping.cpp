#include "grouping.hpp"


using namespace node::operators;

using namespace visitor;

Grouping::Grouping(NodePtr&& t_expr)
  : UnaryOperator{Precedence::GROUPING, std::forward<NodePtr>(t_expr)}
{}

auto Grouping::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
