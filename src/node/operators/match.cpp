#include "match.hpp"


using namespace nodes::operators;

Match::Match(MatchOp t_op, NodePtr&& t_string, NodePtr&& t_pattern)
  : BinaryOperator{Precedence::MATCH, Associativity::NONE,
                   std::forward<NodePtr>(t_string),
                   std::forward<NodePtr>(t_pattern)},
    m_op{t_op}
{}

auto Match::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
