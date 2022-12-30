#ifndef DYNAMIC_OPERATOR_H
#define DYNAMIC_OPERATOR_H

#include <vector>

#include "../expression.hpp"
#include "operators.hpp"


class operators::DynamicOperator : public Expression
{
  std::vector<NodePtr> m_nodes;

  public:
};

#endif // DYNAMIC_OPERATOR_H
