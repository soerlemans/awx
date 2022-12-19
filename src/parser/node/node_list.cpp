#include "node_list.hpp"


NodeList::NodeList()
  :Node{NodeType::NODE_LIST}, m_node_list{}
{}

auto NodeList::accept(NodeVisitor t_visitor) -> void
{

}
