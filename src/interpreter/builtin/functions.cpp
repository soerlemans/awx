#include "functions.hpp"

// STL Includes:
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ranges>
#include <regex>

// Includes:
#include "../any.hpp"


// Using statements:
using namespace interpreter;

// Private data:
namespace {
//! This global is used for the srand and rad
double g_seed{0.0};

// TODO: Use std::ranges
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
  // Lookout narrowing conversion!
  double seed{(double)std::time(nullptr)};

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
auto gsub(const std::string t_pat, const std::string t_rep,
          std::string& t_target) -> double
{
  std::regex re{t_pat};

  t_target = std::regex_replace(t_target, re, t_rep);

  return 0.0;
}

auto index(const std::string t_str, const std::string t_find) -> double
{
  auto pos{t_str.find(t_find)};
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

auto match(const std::string t_str, const std::string t_pat, double& t_rstart,
           double& t_rlength) -> double
{
  std::regex re{t_pat, std::regex::extended};
  std::smatch matches;

  std::regex_search(t_str, matches, re);

  if(matches.empty()) {
    t_rstart = 0.0;
    t_rlength = -1.0;
  } else {
    t_rstart = matches.position() + 1.0;
    t_rlength = matches.length();
  }

  return t_rstart;
}

auto split(const Any& t_str, Any& t_array, const Any& t_fs) -> double
{
  // TODO: Implement arrays

  return 0.0;
}

auto sprintf(const Any& t_fmt, const std::vector<Any>& t_params) -> std::string
{}

auto sub(const std::string t_pat, const std::string t_rep,
         std::string& t_target) -> double
{
  using namespace std::regex_constants;

  std::regex re{t_pat};

  t_target = std::regex_replace(t_target, re, t_rep, format_first_only);

  return 0.0;
}

auto substr(const std::string t_str, const double t_start) -> std::string
{
  return substr(t_str, t_start, (double)std::string::npos);
}

auto substr(const std::string t_str, const double t_start, const double t_count)
  -> std::string
{
  // Bounds checking
  if(t_start > t_str.size()) {
    return "";
  }

  return t_str.substr(t_start, t_count);
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
auto close(const double t_fd) -> double
{
  // TODO: Implement
  return 1.0;
}

auto system(const std::string t_cmd) -> double
{
  return std::system(t_cmd.c_str());
}
} // namespace interpreter::builtin
