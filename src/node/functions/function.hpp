#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "../list.hpp"
#include "../node_interface.hpp"

#include "functions.hpp"

namespace node::functions {
class Function : public NodeInterface {
  private:
  std::string m_name;
  NodeListPtr m_params;
  NodeListPtr m_body;

  public:
  Function(std::string t_name, NodeListPtr&& t_params, NodeListPtr&& t_body);

  auto name() const -> std::string_view;
  auto params() -> NodeListPtr&;
  auto body() -> NodeListPtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Function() override = default;
};
} // namespace node::functions

#endif // FUNCTION_HPP
