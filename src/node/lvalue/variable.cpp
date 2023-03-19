#include "variable.hpp"


using namespace node::lvalue;

using namespace visitor;

Variable::Variable(const std::string& t_name): m_name{std::move(t_name)}
{}

auto Variable::name() const -> const std::string&
{
  return m_name;
}

auto Variable::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
