#include "printf.hpp"

// STL Includes:
#include <utility>


using namespace node::io;

using namespace visitor;

Printf::Printf(NodePtr&& t_format, NodeListPtr&& t_params)
  : m_format{std::forward<NodePtr>(t_format)},
    m_params{std::forward<NodeListPtr>(t_params)}
{}

auto Printf::format() -> NodePtr&
{
  return m_format;
}

auto Printf::params() -> NodeListPtr&
{
  return m_params;
}

