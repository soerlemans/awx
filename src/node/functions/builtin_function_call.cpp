#include "builtin_function_call.hpp"


using namespace node::functions;

using namespace visitor;

BuiltinFunctionCall::BuiltinFunctionCall(std::string&& t_name,
                                         NodeListPtr&& t_args)
  : m_identifier{std::move(t_name)}, m_args{std::forward<NodeListPtr>(t_args)}
{}

auto BuiltinFunctionCall::identifier() const -> std::string_view
{
  return {m_identifier};
}

auto BuiltinFunctionCall::args() -> NodeListPtr&
{
  return m_args;
}
