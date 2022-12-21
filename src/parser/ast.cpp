#include "ast.hpp"


Ast::Ast(NodeList&& t_list)
  : m_root{nullptr}, m_current{nullptr}, m_list{std::forward<NodeList>(t_list)}
{
  // TODO: Implement error handling
  // if(m_list.empty)
  // 	throw 10;

  // m_root = m_list.front().get();
  // m_current = m_root;
}

auto Ast::add(NodePointer&& t_node) -> void
{
  m_list.add(std::forward<NodePointer>(t_node));
}

Ast::~Ast()
{}
