#ifndef AWX_NODE_OPERATORS_MATCH_HPP
#define AWX_NODE_OPERATORS_MATCH_HPP

#include "binary_operator.hpp"
#include "operators.hpp"


namespace node::operators {
enum class MatchOp { MATCH, NO_MATCH };

// EreMatch:
class Match : public BinaryOperator {
  private:
  MatchOp m_op;

  public:
  Match(MatchOp t_op, NodePtr&& t_string, NodePtr&& t_pattern);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Match() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_MATCH_HPP
