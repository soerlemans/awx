#ifndef AWX_NODE_LVALUE_VARIABLE_HPP
#define AWX_NODE_LVALUE_VARIABLE_HPP

#include <string_view>

#include "../node_interface.hpp"

#include "lvalue.hpp"


namespace node::lvalue {
class Variable : public NodeInterface {
  private:
  std::string m_name;

  public:
  Variable(const std::string& t_name);

  auto name() const -> const std::string&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Variable() override = default;
};
} // namespace node::lvalue

#endif // AWX_NODE_LVALUE_VARIABLE_HPP
