#include "node_list.hpp"
#include <utility>


NodeList::NodeList(): Node{NodeType::NODE_LIST}, m_list{}
{
}

auto NodeList::begin() -> std::list<NodePtr>::iterator
{
  return m_list.begin();
}

auto NodeList::end() -> std::list<NodePtr>::iterator
{
  return m_list.end();
}

auto NodeList::add(NodePtr&& t_node) -> void
{
  m_list.push_back(std::forward<NodePtr>(t_node));
}

auto NodeList::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
}

auto NodeList::print() const -> void
{
  for(auto& ptr : m_list)
	ptr->print();
}
