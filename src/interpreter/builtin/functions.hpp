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

// Functions:
auto atan2() -> Any;
auto close() -> Any;
auto cos() -> Any;
auto exp() -> Any;
auto gsub() -> Any;
auto extract_int() -> Any;
auto index() -> Any;
auto length() -> Any;
auto log() -> Any;
auto match() -> Any;
auto rand() -> Any;
auto sin() -> Any;
auto split() -> Any;
auto sprintf() -> Any;
auto sqrt() -> Any;
auto srand() -> Any;
auto sub() -> Any;
auto substr() -> Any;
auto system() -> Any;
auto tolower(const Any& t_str) -> std::string;
auto toupper(const Any& t_any) -> std::string;
} // namespace interpreter::builtin

#endif // AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
