#ifndef RVALUE_H
#define RVALUE_H

#include "../nodes.hpp"

namespace nodes::rvalue {
template<typename T>
class Literal;

// Aliases:
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;
}; // namespace nodes::rvalue

#endif // RVALUE_H
