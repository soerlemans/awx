#include "function.hpp"


using namespace nodes::functions;

Function::Function(std::string t_name, NodeListPtr&& t_params,
                   NodeListPtr&& t_body)
  : Node{NodeType::FUNCTION},
    m_name{std::move(t_name)},
    m_params{std::forward<NodeListPtr>(t_params)},
    m_body{std::forward<NodeListPtr>(t_body)}
{}

auto Function::accept(NodeVisitor t_visitor) -> void
{}

auto Function::print() const -> void
{}

Function::~Function()
{}
