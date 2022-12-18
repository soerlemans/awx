#ifndef DYNAMIC_OPERATOR_H
#define DYNAMIC_OPERATOR_H

#include <vector>

#include "operators.hpp"
#include "../expression.hpp"


class operators::DynamicOperator : public Expression {
  std::vector<StatementPointer> m_statements;
public:

};

#endif // DYNAMIC_OPERATOR_H
