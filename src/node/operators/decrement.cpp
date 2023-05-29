#include "decrement.hpp"


using namespace node::operators;

using namespace visitor;

Decrement::Decrement(NodePtr&& t_left, bool t_prefix)
  : UnaryOperator{Precedence::POSTFIX_INC_DEC, std::forward<NodePtr>(t_left)},
    m_prefix{t_prefix}
{}
