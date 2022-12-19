#include "ast.hpp"


Ast::Ast()
  : m_root{}, m_current{}, m_list({})
{}

auto Ast::add(NodePointer&& t_node) -> void
{
  m_list.add(std::forward<NodePointer>(t_node));
}

Ast::~Ast()
{}
