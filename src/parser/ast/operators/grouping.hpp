#ifndef GROUPING_H
#define GROUPING_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::Grouping : public operators::UnaryOperator {
private:
public:
  virtual ~Grouping();
};

#endif // GROUPING_H
