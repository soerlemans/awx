#include <cassert>
#include <type_traits>
#include <utility>

#include "node.hpp"


using namespace nodes;

Node::Node(NodeType t_nodetype): m_nodetype{t_nodetype}
{}

auto Node::type() -> NodeType
{
  return m_nodetype;
}

Node::~Node()
{}
