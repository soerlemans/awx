#include "assignment.hpp"


using namespace operators;


Assignment::Assignment(AssignmentOp t_op, NodePtr&& t_left,
                       NodePtr&& t_right)
  : BinaryOperator{Precedence::ASSIGNMENT, Associativity::RIGHT,
                   std::forward<NodePtr>(t_left),
                   std::forward<NodePtr>(t_right)},
    m_op{t_op}
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
