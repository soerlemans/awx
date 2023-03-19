#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string_view>

#include "../node_interface.hpp"

#include "lvalue.hpp"


namespace node::lvalue {
class Variable : public NodeInterface {
  private:
  std::string m_name;

  public:
  Variable(const std::string& t_name);

  auto name() const -> std::string_view;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Variable() override = default;
};
} // namespace node::lvalue

#endif // VARIABLE_HPP
