#include "builtin_function_call.hpp"


using namespace node::functions;

using namespace visitor;

BuiltinFunctionCall::BuiltinFunctionCall(std::string&& t_name,
                                         NodeListPtr&& t_args)
  : m_name{std::move(t_name)}, m_args{std::forward<NodeListPtr>(t_args)}
{}

auto BuiltinFunctionCall::name() const -> std::string_view
{
  return {m_name};
}

auto BuiltinFunctionCall::args() -> NodeListPtr&
{
  return m_args;
}

auto BuiltinFunctionCall::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
