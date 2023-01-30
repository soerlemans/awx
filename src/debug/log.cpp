#include "log.hpp"

#include "../enum.hpp"


// Macros:
// Stringify the given log leven in a case
#define CASE_STRINGIFY_LOGLEVEL(loglevel) \
  case LogLevel::loglevel:                \
    return {#loglevel};

namespace {
// Private variables:
log::LogLevel g_loglevel{log::LogLevel::WARNING};
} // namespace

namespace log {
// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
// t_loglevel is used in macros use [[maybe_unused]] to silence warnings
[[nodiscard]] auto is_lower_loglevel(const LogLevel t_loglevel) -> bool
{
  return enum2underlying_type(g_loglevel) >= enum2underlying_type(t_loglevel);
}

auto loglevel2str(const LogLevel t_loglevel) -> std::string_view
{
  switch(t_loglevel) {
    CASE_STRINGIFY_LOGLEVEL(DEBUG);
    CASE_STRINGIFY_LOGLEVEL(INFO);
    CASE_STRINGIFY_LOGLEVEL(WARNING);
    CASE_STRINGIFY_LOGLEVEL(CRITICAL);

    default:
      // TODO: Error or handle unknown loglevel
      break;
  }

  return {"NONE"};
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}
} // namespace log
