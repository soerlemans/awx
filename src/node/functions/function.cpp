#include "function.hpp"


using namespace nodes::functions;

Function::Function(std::string t_name, NodeListPtr&& t_params,
                   NodeListPtr&& t_body)
  : Node{NodeType::FUNCTION},
    m_name{std::move(t_name)},
    m_params{std::forward<NodeListPtr>(t_params)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto Function::name() const -> std::string_view
{
  return {m_name};
}

auto Function::params() -> NodeListPtr&
{
  return m_params;
}

auto Function::body() -> NodeListPtr&
{
  return m_body;
}

auto Function::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
