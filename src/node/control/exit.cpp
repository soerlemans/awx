#include "exit.hpp"


using namespace node::control;

using namespace visitor;

Exit::Exit(NodePtr&& t_expr): m_expr{std::forward<NodePtr>(t_expr)}
{}

