#include "assignment.hpp"


using namespace operators;


Assignment::Assignment(AssignmentOperation t_operation, NodePtr&& t_left,
                       NodePtr&& t_right)
  : BinaryOperator{Precedence::Assignment, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_operation{t_operation}
{}

auto Assignment::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{
  //
}

auto Assignment::print() const -> void
{


}

Assignment::~Assignment()
{}
