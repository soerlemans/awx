#ifndef BUILTIN_FUNCTION_HPP
#define BUILTIN_FUNCTION_HPP

#include "../list.hpp"

#include "functions.hpp"

// TODO: Maybe just inherit from Function?
namespace node::functions {
class BuiltinFunction : public NodeInterface {
  private:
  std::string m_name;
  NodeListPtr m_params;
  NodeListPtr m_body;

  public:
  BuiltinFunction(std::string t_name, NodeListPtr&& t_params,
                  NodeListPtr&& t_body);

  auto name() const -> std::string_view;
  auto params() -> NodeListPtr&;
  auto body() -> NodeListPtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~BuiltinFunction() override = default;
};
} // namespace node::functions

#endif // BUILTIN_FUNCTION_HPP
