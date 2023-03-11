#ifndef LITERAL_HPP
#define LITERAL_HPP

#include <string>
#include <variant>

#include "../../types.hpp"

#include "../node_interface.hpp"
#include "../node.hpp"


namespace node::rvalue {
// Classes:
template<typename T>
class Literal : public NodeInterface {
  private:
  T m_value;

  public:
  Literal(const T t_value): m_value{t_value}
  {}

  auto get() -> T
  {
    return m_value;
  }

  auto accept(NodeVisitor* t_visitor) -> void override
  {
    t_visitor->visit(this);
  }

  ~Literal() override = default;
};
} // namespace node::rvalue

#endif // LITERAL_HPP
