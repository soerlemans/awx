#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include <variant>

#include "../../types.hpp"

#include "../node.hpp"
#include "../nodes.hpp"


namespace nodes::rvalue {
// Classes:
template<typename T>
class Literal : public Node {
  private:
  T m_value;

  public:
  Literal(const T t_value): Node{NodeType::LITERAL}, m_value{t_value}
  {}

  auto get() -> T
  {
    return m_value;
  }

  virtual auto accept(NodeVisitor* t_visitor) -> void override
  {
	t_visitor->visit(this);
  }

  virtual ~Literal()
  {}
};
}; // namespace nodes::rvalue

#endif // LITERAL_H
