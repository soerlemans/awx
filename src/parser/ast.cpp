#include "ast.hpp"


Ast::Ast(): m_root{nullptr}, m_current{nullptr}, m_list{}
{
}

auto Ast::add(NodePtr&& t_node) -> void
{
  m_list.add(std::forward<NodePtr>(t_node));
}

Ast::~Ast()
{
}

// Exported functions:
auto print_ast(const Ast& t_ast) -> void
{
}
