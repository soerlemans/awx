#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include <variant>

#include "../types.hpp"

#include "node.hpp"


// Forward declarations:
template<typename T>
class Literal;

// Aliases:
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;

// Classes:
template<typename T>
class Literal : public Node
{
  private:
  T m_value;

  public:
  Literal(const T t_value): m_value{t_value}
  {
  }

  auto get() -> T
  {
    return m_value;
  }

  virtual ~Literal()
  {
  }
};

#endif // LITERAL_H
