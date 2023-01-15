#include "literal.hpp"

using namespace nodes::rvalue;

template<typename T>
auto Literal<T>::accept(NodeVisitor t_visitor) -> void
{}

template<typename T>
auto Literal<T>::print() const -> void
{}
