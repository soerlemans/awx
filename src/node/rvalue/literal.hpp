#ifndef AWX_NODE_RVALUE_LITERAL_HPP
#define AWX_NODE_RVALUE_LITERAL_HPP

#include <string>
#include <variant>

#include "../../types.hpp"

#include "../node.hpp"
#include "../node_interface.hpp"


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

  auto accept(visitor::NodeVisitor* t_visitor) -> void override
  {
    t_visitor->visit(this);
  }

  ~Literal() override = default;
};
} // namespace node::rvalue

#endif // AWX_NODE_RVALUE_LITERAL_HPP
