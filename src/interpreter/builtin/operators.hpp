#ifndef INTERPRETER_BUILTIN_OPERATORS_HPP
#define INTERPRETER_BUILTIN_OPERATORS_HPP

// STL Includes:
#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

// Includes:
#include "../convert.hpp"


namespace interpreter::builtin {
// Public functions:
// Arithmetic:
/*! Power uses a function and can not be defined using the
 * INTERPRETER_DEFINE_BINOP_FUNCTION macro
 */
template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto power(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return std::pow(t_lhs, t_rhs);
  }};

  return convert(lambda, t_lhs, t_rhs);
}

INTERPRETER_DEFINE_BINOP_FUNCTION(*, multiply)
INTERPRETER_DEFINE_BINOP_FUNCTION(/, divide)

// Modulo can not use this macro either
// INTERPRETER_DEFINE_BINOP_FUNCTION(%, modulo)

INTERPRETER_DEFINE_BINOP_FUNCTION(+, add)
INTERPRETER_DEFINE_BINOP_FUNCTION(-, subtract)

// Comparisons:
INTERPRETER_DEFINE_BINOP_FUNCTION(<, less_than)
INTERPRETER_DEFINE_BINOP_FUNCTION(<=, less_than_equal)

INTERPRETER_DEFINE_BINOP_FUNCTION(==, equal)
INTERPRETER_DEFINE_BINOP_FUNCTION(!=, not_equal)

INTERPRETER_DEFINE_BINOP_FUNCTION(>, greater_than)
INTERPRETER_DEFINE_BINOP_FUNCTION(>=, greater_than_equal)
} // namespace interpreter::builtin

#endif // INTERPRETER_BUILTIN_OPERATORS_HPP
