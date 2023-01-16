#ifndef ERE_H
#define ERE_H

#include "binary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
// EreMatch:
class EreMatch : public BinaryOperator {
  private:
  public:
  virtual ~EreMatch();
};

// EreNonMatch:
class EreNonMatch : public BinaryOperator {
  private:
  public:
  virtual ~EreNonMatch();
};
}; // namespace nodes::operators

#endif // ERE_H
