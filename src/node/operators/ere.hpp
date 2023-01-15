#ifndef ERE_H
#define ERE_H

#include "operators.hpp"
#include "binary_operator.hpp"


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
