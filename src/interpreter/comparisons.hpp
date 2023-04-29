#ifndef INTERPRETER_COMPARISONS_HPP
#define INTERPRETER_COMPARISONS_HPP

// STL Includes:
#include <sstream>
#include <string>
#include <type_traits>

// Local Includes:
#include "convert.hpp"

namespace interpreter {

// Public functions:
template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto less_than(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs < t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto less_than_equal(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs <= t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto equal(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs == t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto not_equal(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs != t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto greater_than(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs >= t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto greater_than_equal(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs >= t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

} // namespace interpreter

#endif // INTERPRETER_COMPARISONS_HPP
