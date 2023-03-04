#ifndef FUNCTION_CALL_HPP
#define FUNCTION_CALL_HPP

#include <string>
#include <string_view>

#include "../list.hpp"
#include "../node.hpp"

#include "functions.hpp"


namespace nodes::functions {
class FunctionCall : public Node {
  private:
  std::string m_name;
  NodeListPtr m_args;

  public:
  FunctionCall(std::string&& t_name, NodeListPtr&& t_args);

  auto name() const -> std::string_view;
  auto args() -> NodeListPtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~FunctionCall() override = default;
};
} // namespace nodes::functions

#endif // FUNCTION_CALL_HPP
