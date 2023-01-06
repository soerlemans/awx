#include "variable.hpp"


Variable::Variable(const std::string t_name)
  : Node{NodeType::VARIABLE}, m_name{t_name}
{}

auto Variable::accept(NodeVisitor t_visitor) -> void
{}

auto Variable::print() const -> void
{}

Variable::~Variable()
{}
