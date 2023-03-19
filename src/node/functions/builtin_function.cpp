#include "builtin_function.hpp"


using namespace node::functions;

using namespace visitor;

BuiltinFunction::BuiltinFunction(std::string t_name, NodeListPtr&& t_params,
                                 NodeListPtr&& t_body)
  : m_name{std::move(t_name)},
    m_params{std::forward<NodeListPtr>(t_params)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto BuiltinFunction::name() const -> std::string_view
{
  return {m_name};
}

auto BuiltinFunction::params() -> NodeListPtr&
{
  return m_params;
}

auto BuiltinFunction::body() -> NodeListPtr&
{
  return m_body;
}

auto BuiltinFunction::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
