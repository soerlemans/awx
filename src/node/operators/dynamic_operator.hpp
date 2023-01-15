#ifndef DYNAMIC_OPERATOR_H
#define DYNAMIC_OPERATOR_H

#include <vector>

#include "../expression.hpp"
#include "operators.hpp"


namespace nodes::operators {
class DynamicOperator : public Expression {
  private:
  std::vector<NodePtr> m_nodes;

  public:
};
}; // namespace nodes::operators

#endif // DYNAMIC_OPERATOR_H
