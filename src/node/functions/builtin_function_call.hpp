#ifndef AWX_NODE_FUNCTIONS_BUILTIN_FUNCTION_CALL_HPP
#define AWX_NODE_FUNCTIONS_BUILTIN_FUNCTION_CALL_HPP

// Includes:
#include "../list.hpp"

// Local Includes:
#include "functions.hpp"


namespace node::functions {
class BuiltinFunctionCall : public NodeInterface {
  private:
  std::string m_name;
  NodeListPtr m_args;

  public:
  BuiltinFunctionCall(std::string&& t_name, NodeListPtr&& t_args);

  auto name() const -> std::string_view;
  auto args() -> NodeListPtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~BuiltinFunctionCall() override = default;
};
} // namespace node::functions

#endif // AWX_NODE_FUNCTIONS_BUILTIN_FUNCTION_CALL_HPP
