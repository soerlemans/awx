#include "string_concatenation.hpp"


using namespace node::operators;

using namespace visitor;

StringConcatenation::StringConcatenation(NodePtr&& t_left, NodePtr&& t_right)
  : BinaryOperator{std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)}
{}
