#include "ast.hpp"


Ast::Ast()
  : m_root{nullptr}, m_current{nullptr}, m_list{}, m_visitor{}
{}

auto Ast::add(NodePointer&& t_node) -> void
{
  // m_list.add(std::forward<NodePointer>(t_node));
}

Ast::~Ast()
{}
