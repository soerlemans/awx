#include "function_call.hpp"


using namespace nodes::functions;

FunctionCall::FunctionCall(std::string t_name, NodeListPtr&& t_args)
  : Node{NodeType::FUNCTION},
    m_name{std::move(t_name)},
    m_args{std::forward<NodeListPtr>(t_args)}
{}

auto FunctionCall::accept(NodeVisitor* t_visitor) -> void
{
  t_visitor->visit(this);
}

FunctionCall::~FunctionCall()
{}
