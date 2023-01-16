#include "list.hpp"

using namespace nodes;

List::List(): Node{NodeType::NODE_LIST}, m_list{}
{}

auto List::begin() -> std::list<NodePtr>::iterator
{
  return m_list.begin();
}

auto List::end() -> std::list<NodePtr>::iterator
{
  return m_list.end();
}

auto List::add(NodePtr&& t_node) -> void
{
  m_list.push_back(std::forward<NodePtr>(t_node));
}

auto List::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{}

auto List::print() const -> void
{
  for(auto& ptr : m_list)
    ptr->print();
}
