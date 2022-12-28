#ifndef DYNAMIC_OPERATOR_H
#define DYNAMIC_OPERATOR_H

#include <vector>

#include "operators.hpp"
#include "../expression.hpp"


class operators::DynamicOperator : public Expression {
  std::vector<NodePointer> m_nodes;
public:

};

#endif // DYNAMIC_OPERATOR_H
