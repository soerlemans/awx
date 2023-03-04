#include "variable.hpp"


using namespace nodes::lvalue;

Variable::Variable(const std::string& t_name): m_name{std::move(t_name)}
{}

auto Variable::name() const -> std::string_view
{
  return {m_name};
}

auto Variable::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
