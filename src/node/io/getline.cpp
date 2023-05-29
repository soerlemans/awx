#include "getline.hpp"

#include <utility>


using namespace node::io;

using namespace visitor;

Getline::Getline(NodePtr&& t_var): m_var{std::forward<NodePtr>(t_var)}
{}

auto Getline::var() -> NodePtr&
{
  return m_var;
}

