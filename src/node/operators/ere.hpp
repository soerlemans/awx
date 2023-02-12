#ifndef ERE_H
#define ERE_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
enum class EreOp { MATCH, NO_MATCH };

// EreMatch:
class Ere : public BinaryOperator {
  private:
  EreOp m_op;

  public:
  Ere(EreOp t_op, NodePtr&& t_string, NodePtr&& t_pattern);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Ere() override = default;
};
} // namespace nodes::operators

#endif // ERE_H
