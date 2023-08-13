#include "functions.hpp"

// STL Includes:
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <regex>

// Includes:
#include "../any.hpp"


// Using statements:
using namespace interpreter;

// Private data:
namespace {
//! This global is used for the srand and rad
double g_seed{0.0};

template<typename Func>
auto transform(const std::string& t_str, Func t_lambda) -> std::string
{
  std::string str{t_str};

  std::transform(str.begin(), str.end(), str.begin(), t_lambda);

  return str;
}
} // namespace

// Exported functions:
namespace interpreter::builtin {
// Builtin functions:
// Arithmetic functions:
auto atan2(const double t_y, const double t_x) -> double
{
  return std::atan2(t_y, t_x);
}

auto cos(const double t_x) -> double
{
  return std::cos(t_x);
}

auto sin(const double t_x) -> double
{
  return std::sin(t_x);
}

auto exp(const double t_x) -> double
{
  return std::exp(t_x);
}

auto log(const double t_x) -> double
{
  return std::log(t_x);
}

auto sqrt(const double t_x) -> double
{
  return std::sqrt(t_x);
}

auto to_int(const double t_any) -> double
{
  return t_any;
}

auto rand() -> double
{
  return std::rand();
}

auto srand() -> double
{
  double seed{std::time(nullptr)};

  return srand(seed);
}

auto srand(const double t_seed) -> double
{
  const auto prev_seed{g_seed};

  g_seed = t_seed;
  std::srand((unsigned)g_seed);

  return prev_seed;
}

// String functions:
// TODO: Must return the match count
auto gsub(const Any& t_regex, const Any& t_rep, Any& t_target) -> double
{
  const auto target{t_target.str()};
  std::regex re{t_regex.str()};

  t_target = std::regex_replace(target, re, t_rep.str());

  return 0.0;
}

auto index(const Any& t_str, const Any& t_find) -> double
{
  const auto str{t_str.str()};
  const auto find{t_find.str()};

  auto pos{str.find(find)};
  if(pos == std::string::npos) {
    pos = 0;
  } else {
    pos++;
  }

  return pos;
}

auto length(const std::string t_str) -> double
{
  return t_str.size();
}

auto match(const Any& t_str, const Any& t_regex) -> double
{}

auto split(const Any& t_str, Any& t_array, const Any& t_fs) -> double
{}

auto sprintf(const Any& t_fmt, const std::vector<Any>& t_params) -> std::string
{}

auto sub(const Any& t_regx, const Any& t_rep, Any& t_target) -> double
{}

auto substr(const Any& t_str, const Any& t_start) -> std::string
{
  return substr(t_str, t_start, (double)std::string::npos);
}

auto substr(const Any& t_str, const Any& t_start, const Any& t_count)
  -> std::string
{
  const auto str{t_str.str()};
  const auto start{t_start.num()};
  const auto count{t_count.num()};

  // Bounds checking
  if(start > str.size()) {
    return "";
  }

  return str.substr(start, count);
}

auto tolower(const std::string t_str) -> std::string
{
  return transform(t_str, [](const unsigned t_char) {
    return std::tolower(t_char);
  });
}

auto toupper(const std::string t_str) -> std::string
{
  return transform(t_str, [](const unsigned t_char) {
    return std::toupper(t_char);
  });
}

// IO and general functions:
auto close(const Any& t_any) -> double
{
  // TODO: Implement
  return 1.0;
}

auto system(const Any& t_any) -> double
{
  const std::string str{t_any.str()};

  return std::system(str.c_str());
}
} // namespace interpreter::builtin
