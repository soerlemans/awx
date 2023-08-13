#ifndef AWX_INTERPRETER_CAST_HPP
#define AWX_INTERPRETER_CAST_HPP

// Local Includes:
#include "context.hpp"
#include "overload.hpp"

/*! In AWK string's are often casted to doubles for a lot of operations.
 * This gets tricky to define manually for binary operations as the down cast to
 * a double only happens when on of the arguments is a double and the other a
 * string. This file defines a template function called convert that does this.
 */


namespace interpreter {
// Macros:
/*! Cookie cut macro for easily defining binary operations that use the convert
 * Function
 */
#define INTERPRETER_DEFINE_BINOP_FUNCTION(op, func_name)                 \
  template<typename L, typename R>                                       \
  inline auto func_name(L&& t_lhs, R&& t_rhs)                            \
  {                                                                      \
    const auto lambda{[](const auto& t_lhs, const auto& t_rhs) {         \
      return t_lhs op t_rhs;                                             \
    }};                                                                  \
                                                                         \
    return cast(lambda, std::forward<L>(t_lhs), std::forward<R>(t_rhs)); \
  }

//! Following macro converts a parameter if it is a string to a double
#define INTERPRETER_CAST_IF_STR(type, dst, src)          \
  do {                                                   \
    if constexpr(std::is_same<std::remove_cvref_t<type>, \
                              std::string>::value) {     \
      dst = cast(src);																	 \
    } else {                                             \
      dst = src;                                         \
    }                                                    \
  } while(false)

// Enums:
// TODO :Implement CastingPolicy
//! CastingPolicy determines if a string is preffered or a number
enum class CastingPolicy { STRING, NUMBER };

// Public Functions:
/*! In some cases a unary operation will need to be converted to a double only
 * if the string starts with a number
 */
inline auto cast(const std::string& t_str) -> double
{
  if(!t_str.empty()) {
    if(std::isdigit(t_str.front())) {
      return std::stod(t_str);
    }
  }

  return 0;
}

constexpr inline auto cast(const double t_val) -> double
{
  return t_val;
}

inline auto cast(const Any& t_val) -> double
{
  return t_val.num();
}

// TODO: Make this variadic
//! Overload for the greedy template down below
template<typename Func>
inline auto cast(Func t_func, const std::string& t_lhs,
                 const std::string& t_rhs)
{
  return t_func(t_lhs, t_rhs);
}

template<typename Func, typename L, typename R>
requires VariableLike<L> && VariableLike<R>
inline auto cast(Func t_func, L t_lhs, R t_rhs)
{
  double lhs, rhs;

  INTERPRETER_CAST_IF_STR(L, lhs, t_lhs);
  INTERPRETER_CAST_IF_STR(R, rhs, t_rhs);

  return t_func(lhs, rhs);
}

template<typename Func>
inline auto cast(Func t_func, const Any& t_lhs, const Any& t_rhs)
{
  return std::visit(
    [&](auto&& t_left, auto&& t_right) {
      using L = decltype(t_left);
      using R = decltype(t_right);

      return cast(t_func, std::forward<L>(t_left), std::forward<R>(t_right));
    },
    t_lhs, t_rhs);
}
} // namespace interpreter

#endif // AWX_INTERPRETER_CAST_HPP
