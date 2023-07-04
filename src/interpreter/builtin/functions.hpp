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
auto gsub() -> Any;
auto index() -> Any;
auto length() -> Any;
auto match() -> Any;
auto split() -> Any;
auto sprintf() -> Any;
auto sub() -> Any;
auto substr() -> Any;
auto tolower(const Any& t_any) -> std::string;
auto toupper(const Any& t_any) -> std::string;

// IO and general functions:
auto close() -> Any;
auto system(const Any& t_any) -> double;
} // namespace interpreter::builtin

#endif // AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
