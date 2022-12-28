#include "node_list.hpp"
#include <utility>


NodeList::NodeList(): Node{NodeType::NODE_LIST}, m_list{}
{}

auto NodeList::add(NodePointer&& t_node) -> void
{
  m_list.push_back(std::forward<NodePointer>(t_node));
}

auto NodeList::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{}
