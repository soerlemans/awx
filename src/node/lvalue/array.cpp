#include "array.hpp"

#include <utility>


using namespace node::lvalue;

using namespace visitor;

Array::Array(std::string t_name, NodePtr&& t_expr_list)
  : Variable{std::move(t_name)}, m_expr_list{std::forward<NodePtr>(t_expr_list)}
{}

