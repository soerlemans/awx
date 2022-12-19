#include "node_list.hpp"


NodeList::NodeList()
  :Node{NodeType::NODE_LIST}, m_node_list{}
{}

auto NodeList::add(NodePointer&& t_node) -> void
{
  m_node_list.push_back(std::forward<NodePointer>(t_node));
}

auto NodeList::accept([[maybe_unused]]NodeVisitor t_visitor) -> void
{

}
