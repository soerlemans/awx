#include "delete.hpp"


using namespace node::operators;

using namespace visitor;

Delete::Delete(std::string&& t_array, NodeListPtr&& t_expr_list)
  : m_array{std::forward<std::string>(t_array)},
    m_expr_list{std::forward<NodeListPtr>(t_expr_list)}
{}

