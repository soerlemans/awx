#include "ast.hpp"


using namespace nodes;

// Methods:
auto Ast::add(NodePtr&& t_node) -> void
{
  m_list.push_back(std::forward<NodePtr>(t_node));
}

auto Ast::current() const -> NodeInterface*
{
  return m_current;
}
