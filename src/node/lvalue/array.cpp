#include "array.hpp"


Array::Array(const std::string t_name): Variable{t_name}
{}

auto Array::accept(NodeVisitor t_visitor) -> void
{}

auto Array::print() const -> void
{}

Array::~Array()
{}
