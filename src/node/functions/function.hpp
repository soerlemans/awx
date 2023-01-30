#ifndef FUNCTION_H
#define FUNCTION_H

#include "../node.hpp"
#include "../list.hpp"

#include "functions.hpp"

namespace nodes::functions {
class Function : public Node {
  private:
  std::string m_name;
  NodeListPtr m_params;
  NodeListPtr m_body;

  public:
  Function(std::string t_name, NodeListPtr&& t_params, NodeListPtr&& t_body);

  auto name() const -> std::string_view;
  auto params() -> NodeListPtr&;
  auto body() -> NodeListPtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Function();
};
} // namespace nodes::functions

#endif // FUNCTION_H