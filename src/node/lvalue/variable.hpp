#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string_view>

#include "../node.hpp"

#include "lvalue.hpp"


namespace nodes::lvalue {
class Variable : public Node {
  private:
  std::string m_name;

  public:
  Variable(std::string t_name);

  auto name() const -> std::string_view;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Variable() override = default;
};
} // namespace nodes::lvalue

#endif // VARIABLE_HPP
