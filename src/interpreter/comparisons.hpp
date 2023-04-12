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
auto equal(const std::string& t_lhs, const std::string& t_rhs) -> bool;

template<typename L, typename R>
requires VariableLike<L> && VariableLike<R>
auto equal(L&& t_lhs, R&& t_rhs) -> bool
{
  double lhs, rhs;

  INTERPRETER_CONVERT_IF_STR(L, lhs, t_lhs);
  INTERPRETER_CONVERT_IF_STR(R, rhs, t_rhs);

  return lhs == rhs;
}
} // namespace interpreter

#endif // INTERPRETER_COMPARISONS_HPP
