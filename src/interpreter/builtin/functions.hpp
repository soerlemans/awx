#ifndef AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
#define AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP

// STL Includes:
#include <cmath>
#include <functional>
#include <map>

// Local Includes:
#include "../context.hpp"


namespace interpreter::builtin {
// Macros:
// #define AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
// {
// #func, func
// }

// Aliases:
using BuiltinFuncPtr = std::function<Any(Any)>;

// Globals:
// extern const std::map<std::string_view, > g_builtin_functions;

// Builtin functions:
// Arithmetic functions:
auto atan2(const Any& t_y, const Any& t_x) -> double;
auto cos(const Any& t_x) -> double;
auto sin(const Any& t_x) -> double;
auto exp(const Any& t_x) -> double;
auto log(const Any& t_x) -> double;
auto sqrt(const Any& t_x) -> double;
auto to_int(const Any& t_any) -> double;
auto rand() -> double;

auto srand() -> double;
auto srand(const Any& t_seed) -> double;

// String functions:
auto gsub(const Any& t_ere, const Any& t_rep, Any& t_target) -> double;
auto index(const Any& t_str, const Any& t_find) -> double;
auto length(const Any& t_any) -> double;
auto match(const Any& t_str, const Any& t_ere) -> double;
auto split(const Any& t_str, Any& t_array, const Any& t_fs) -> double;
auto sprintf(const Any& t_fmt, const std::vector<Any>& t_params) -> std::string;
auto sub(const Any& t_ere, const Any& t_rep, Any& t_target) -> double;
auto substr(const Any& t_str, const Any& t_start, const Any& t_count)
  -> std::string;
auto tolower(const Any& t_any) -> std::string;
auto toupper(const Any& t_any) -> std::string;

// IO and general functions:
auto close() -> Any;
auto system(const Any& t_any) -> double;
} // namespace interpreter::builtin

#endif // AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
