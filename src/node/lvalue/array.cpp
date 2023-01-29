#include "array.hpp"

#include <utility>


using namespace nodes::lvalue;

Array::Array(std::string t_name, NodePtr&& t_expr_list)
  : Variable{std::move(t_name)}, m_expr_list{std::forward<NodePtr>(t_expr_list)}
{}

auto Array::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

Array::~Array()
{}
