#ifndef RVALUE_H
#define RVALUE_H

#include "../nodes.hpp"

namespace nodes::rvalue {
template<typename T>
class Literal;

class Regex;

// Aliases:
// TODO: Think about a way to convey Regex literals
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;
} // namespace nodes::rvalue

#endif // RVALUE_H
