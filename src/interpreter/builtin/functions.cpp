#include "functions.hpp"

// STL Includes:
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

// Includes:
#include "../cast.hpp"
#include "../stringify.hpp"


// Using statements:
using namespace interpreter;

// Private data:
namespace {
//! This global is used for the srand and rad
double g_seed{0.0};

template<typename Func>
auto transform(const Any& t_any, Func t_lambda) -> std::string
{
  std::string str{stringify(t_any)};

  std::transform(str.begin(), str.end(), str.begin(), t_lambda);

  return str;
}
} // namespace

// Exported functions:
namespace interpreter::builtin {
// Builtin functions:
// Arithmetic functions:
auto atan2(const Any& t_y, const Any& t_x) -> double
{
  return std::atan2(cast(t_y), cast(t_x));
}

auto cos(const Any& t_x) -> double
{
  return std::cos(cast(t_x));
}

auto sin(const Any& t_x) -> double
{
  return std::sin(cast(t_x));
}

auto exp(const Any& t_x) -> double
{
  return std::exp(cast(t_x));
}

auto log(const Any& t_x) -> double
{
  return std::log(cast(t_x));
}

auto sqrt(const Any& t_x) -> double
{
  return std::sqrt(cast(t_x));
}

auto to_int(const Any& t_any) -> double
{
  return cast(t_any);
}

auto rand() -> double
{
  Any seed{(double)std::time(nullptr)};

  return srand(seed);
}

auto srand(const Any& t_seed) -> double
{
  const auto prev_seed{g_seed};

  g_seed = cast(t_seed);
  std::srand((unsigned)g_seed);

  return prev_seed;
}

// String functions:
// TODO: tolower and toupper are similar, create a
auto tolower(const Any& t_any) -> std::string
{
  return transform(t_any, [](const unsigned t_char) {
    return std::tolower(t_char);
  });
}

auto toupper(const Any& t_any) -> std::string
{
  return transform(t_any, [](const unsigned t_char) {
    return std::toupper(t_char);
  });
}

// IO and general functions:
auto system(const Any& t_any) -> double
{
  const std::string str{stringify(t_any)};

  return std::system(str.c_str());
}
} // namespace interpreter::builtin
