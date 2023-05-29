#ifndef AWX_NODE_FUNCTIONS_FUNCTION_CALL_HPP
#define AWX_NODE_FUNCTIONS_FUNCTION_CALL_HPP

#include <string>
#include <string_view>

#include "../list.hpp"
#include "../node_interface.hpp"

#include "functions.hpp"


namespace node::functions {
class FunctionCall : public NodeInterface {
  private:
  std::string m_name;
  NodeListPtr m_args;

  public:
  FunctionCall(std::string&& t_name, NodeListPtr&& t_args);

  auto name() const -> std::string_view;
  auto args() -> NodeListPtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~FunctionCall() override = default;
};
} // namespace node::functions

#endif // AWX_NODE_FUNCTIONS_FUNCTION_CALL_HPP
