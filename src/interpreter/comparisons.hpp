#ifndef INTERPRETER_COMPARISONS_HPP
#define INTERPRETER_COMPARISONS_HPP

// STL Includes:
#include <sstream>
#include <string>
#include <type_traits>

// Local Includes:
#include "context.hpp"

namespace interpreter {
// Macros:
//! Following macro converts string's to doubles
#define INTERPRETER_CONVERT_IF_STR(type, dst, src)       \
  do {                                                   \
    if constexpr(std::is_same<std::remove_cvref_t<type>, \
                              std::string>::value) {     \
      dst = std::stod(src);                              \
    } else {                                             \
      dst = src;                                         \
    }                                                    \
  } while(false)

// Concepts:
template<typename T>
concept VariableLike = std::same_as < std::remove_cvref_t<T>,
double > || std::same_as<std::remove_cvref_t<T>, std::string>;

// Public functions:
template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto equal(L t_lhs, R t_rhs) -> bool
{
  const auto lambda{[](const auto& t_lhs, const auto& t_rhs) -> bool {
    return t_lhs == t_rhs;
  }};

  return convert(lambda, t_lhs, t_rhs);
}

template<typename T>
auto convert(T t_func, const std::string& t_lhs, const std::string& t_rhs)
{
  return t_func(t_lhs, t_rhs);
}

template<typename T, typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto convert(T t_func, L t_lhs, R t_rhs)
{
  double lhs, rhs;

  INTERPRETER_CONVERT_IF_STR(L, lhs, t_lhs);
  INTERPRETER_CONVERT_IF_STR(R, rhs, t_rhs);

  return t_func(lhs, rhs);
}
} // namespace interpreter

#endif // INTERPRETER_COMPARISONS_HPP
