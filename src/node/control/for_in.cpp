#include "for_in.hpp"


using namespace node::control;

using namespace visitor;

ForIn::ForIn(NodePtr&& t_identifier, NodePtr&& t_array, NodeListPtr&& t_body)
  : m_identifier{std::forward<NodePtr>(t_identifier)},
    m_array{std::forward<NodePtr>(t_array)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

