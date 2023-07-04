#ifndef AWX_INTERPRETER_BUILTIN_OPERATORS_HPP
#define AWX_INTERPRETER_BUILTIN_OPERATORS_HPP

// STL Includes:
#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

// Includes:
#include "../cast.hpp"


namespace interpreter::builtin {
// Public functions:
// Arithmetic:
/*! Power uses a function and can not be defined using the
 * INTERPRETER_DEFINE_BINOP_FUNCTION macro
 */
template<typename L, typename R>
auto power(L&& t_lhs, R&& t_rhs)
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) {
    return std::pow(t_lhs, t_rhs);
  }};

  return cast(lambda, std::forward<L>(t_lhs), std::forward<R>(t_rhs));
}

INTERPRETER_DEFINE_BINOP_FUNCTION(*, multiply)
INTERPRETER_DEFINE_BINOP_FUNCTION(/, divide)

// Modulo can not use this macro either
// FIXME: std::fmod not working?
template<typename L, typename R>
auto modulo(L&& t_lhs, R&& t_rhs)
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) {
    return std::fmod(t_lhs, t_rhs);
  }};

  return cast(lambda, std::forward<L>(t_lhs), std::forward<R>(t_rhs));
}


INTERPRETER_DEFINE_BINOP_FUNCTION(+, add)
INTERPRETER_DEFINE_BINOP_FUNCTION(-, subtract)

// Comparisons:
// FIXME: We are comparing these as doubles now which is not a good idea
INTERPRETER_DEFINE_BINOP_FUNCTION(<, less_than)
INTERPRETER_DEFINE_BINOP_FUNCTION(<=, less_than_equal)

INTERPRETER_DEFINE_BINOP_FUNCTION(==, equal)
INTERPRETER_DEFINE_BINOP_FUNCTION(!=, not_equal)

INTERPRETER_DEFINE_BINOP_FUNCTION(>, greater_than)
INTERPRETER_DEFINE_BINOP_FUNCTION(>=, greater_than_equal)
} // namespace interpreter::builtin

#endif // AWX_INTERPRETER_BUILTIN_OPERATORS_HPP
