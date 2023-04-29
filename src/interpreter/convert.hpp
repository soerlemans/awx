#ifndef INTERPRETER_CONVERT_HPP
#define INTERPRETER_CONVERT_HPP

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


// Public Functions:
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

#endif // INTERPRETER_CONVERT_HPP
