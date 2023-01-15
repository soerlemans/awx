#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include <variant>

#include "../../types.hpp"

#include "../nodes.hpp"
#include "../node.hpp"


namespace nodes::rvalue {
// Classes:
template<typename T>
class Literal : public Node {
  private:
  T m_value;

  public:
  Literal(const T t_value): m_value{t_value}
  {}

  auto get() -> T
  {
    return m_value;
  }

  virtual ~Literal()
  {}
};
}; // namespace nodes::rvalue

#endif // LITERAL_H
