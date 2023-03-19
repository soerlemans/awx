#include "function_call.hpp"


using namespace node::functions;

using namespace visitor;

FunctionCall::FunctionCall(std::string&& t_name, NodeListPtr&& t_args)
  : m_name{std::move(t_name)}, m_args{std::forward<NodeListPtr>(t_args)}
{}

auto FunctionCall::name() const -> std::string_view
{
  return {m_name};
}

auto FunctionCall::args() -> NodeListPtr&
{
  return m_args;
}

auto FunctionCall::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
