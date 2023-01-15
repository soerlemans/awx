#include "variable.hpp"


using namespace nodes::lvalue;

Variable::Variable(const std::string t_name)
  : Node{NodeType::VARIABLE}, m_name{t_name}
{}

auto Variable::accept(NodeVisitor t_visitor) -> void
{}

auto Variable::print() const -> void
{}

Variable::~Variable()
{}
