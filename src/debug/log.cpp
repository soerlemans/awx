#include "log.hpp"

#include "../enum.hpp"


using namespace debug;

namespace {
// Private variables:
LogLevel g_loglevel{LogLevel::WARNING};
} // namespace

namespace debug {
// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
// t_loglevel is used in macros use [[maybe_unused]] to silence warnings
// TOOD: This could be constexpr
[[nodiscard]] auto is_lower_loglevel(const LogLevel t_loglevel) -> bool
{
  return enum2underlying_type(g_loglevel) >= enum2underlying_type(t_loglevel);
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}
} // namespace debug
