#ifndef ERE_H
#define ERE_H

#include "binary_operator.hpp"
#include "operators.hpp"


// EreMatch:
class operators::EreMatch : public operators::BinaryOperator
{
  private:
  public:
  virtual ~EreMatch();
};

// EreNonMatch:
class operators::EreNonMatch : public operator ::BinaryOperator
{
  private:
  public:
  virtual ~EreNonMatch();
};

#endif // ERE_H
