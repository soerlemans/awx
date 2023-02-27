#include "delete.hpp"


using namespace nodes::operators;

Delete::Delete(std::string&& t_array, NodeListPtr&& t_expr_list)
  : m_array{std::forward<std::string>(t_array)},
    m_expr_list{std::forward<NodeListPtr>(t_expr_list)}
{}

auto Delete::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}
