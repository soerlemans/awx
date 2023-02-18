#ifndef MATCH_H
#define MATCH_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
enum class MatchOp { MATCH, NO_MATCH };

// EreMatch:
class Match : public BinaryOperator {
  private:
  MatchOp m_op;

  public:
  Match(MatchOp t_op, NodePtr&& t_string, NodePtr&& t_pattern);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Match() override = default;
};
} // namespace nodes::operators

#endif // MATCH_H
