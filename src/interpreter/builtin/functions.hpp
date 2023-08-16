#ifndef AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
#define AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP

// STL Includes:
#include <cmath>
#include <functional>
#include <map>

// Local Includes:
#include "../context.hpp"


namespace interpreter::builtin {
// Aliases:
using BuiltinFuncPtr = std::function<Any(Any)>;

// Builtin functions:
// Arithmetic functions:
auto atan2(const double t_y, const double t_x) -> double;
auto cos(const double t_x) -> double;
auto sin(const double t_x) -> double;
auto exp(const double t_x) -> double;
auto log(const double t_x) -> double;
auto sqrt(const double t_x) -> double;
auto to_int(const double t_any) -> double;
auto rand() -> double;
auto srand() -> double;
auto srand(const double t_seed) -> double;

// String functions:
auto gsub(const std::string t_pat, const std::string t_rep,
          std::string& t_target) -> double;
auto index(const Any& t_str, const Any& t_find) -> double;
auto length(const std::string t_str) -> double;
auto match(const std::string& t_str, const std::string& t_pat, double& t_rstart,
           double& t_rlenght) -> double;
auto split(const Any& t_str, Any& t_array, const Any& t_fs) -> double;
auto sprintf(const Any& t_fmt, const std::vector<Any>& t_params) -> std::string;
auto sub(const std::string& t_ere, const std::string& t_rep,
         std::string& t_target) -> double;
auto substr(const Any& t_str, const Any& t_start) -> std::string;
auto substr(const Any& t_str, const Any& t_start, const Any& t_count)
  -> std::string;
auto tolower(const std::string t_str) -> std::string;
auto toupper(const std::string t_str) -> std::string;

// IO and general functions:
auto close(const Any& t_any) -> double;
auto system(const Any& t_any) -> double;
} // namespace interpreter::builtin

#endif // AWX_INTERPRETER_BUILTIN_FUNCTIONS_HPP
