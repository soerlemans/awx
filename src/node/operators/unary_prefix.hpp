#ifndef UNARY_PREFIX_H
#define UNARY_PREFIX_H

#include "operators.hpp"
#include "unary_operator.hpp"


class operators::UnaryPrefix : public operators::UnaryOperator {
private:
public:
  UnaryPrefix();
  virtual ~UnaryPrefix();
};

#endif // UNARY_PREFIX_H
