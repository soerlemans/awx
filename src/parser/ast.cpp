#include "ast.hpp"


using namespace nodes;

// Constructor:
Ast::Ast(): m_root{nullptr}, m_current{nullptr}, m_list{}
{}

// Methods:
auto Ast::add(NodePtr&& t_node) -> void
{
  m_list.push_back(std::forward<NodePtr>(t_node));
}

auto Ast::current() const -> Node*
{
  return m_current;
}

// Destructor:
Ast::~Ast()
{}
