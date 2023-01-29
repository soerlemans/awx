#include "variable.hpp"


using namespace nodes::lvalue;

Variable::Variable(std::string t_name)
  : Node{NodeType::VARIABLE}, m_name{std::move(t_name)}
{}

auto Variable::accept(NodeVisitor t_visitor) -> void
{}

auto Variable::print() const -> void
{}

Variable::~Variable()
{}
