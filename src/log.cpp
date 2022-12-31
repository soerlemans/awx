#include "log.hpp"


// Macros:
// Stringify the given log leven in a case
#define CASE_STRINGIFY_LOGLEVEL(loglevel) \
  case LogLevel::loglevel:                \
    return {#loglevel};

// Compare the global and given log level within a case statement
#define CASE_EQUAL_LOGLEVEL(loglevel) \
  case loglevel:                      \
    do {                              \
      if(g_loglevel == loglevel) {    \
        return true;                  \
      }                               \
    } while(0)

namespace
{
// Private variables:
log::LogLevel g_loglevel{log::LogLevel::WARNING};
}; // namespace

namespace log
{
// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
// t_loglevel is used in macros use [[maybe_unused]] to silence warnings
auto is_lower_loglevel([[maybe_unused]] const LogLevel t_loglevel) -> bool
{
  switch(g_loglevel) {
    // These macros use the return statement
    CASE_EQUAL_LOGLEVEL(LogLevel::DEBUG);
    [[fallthrough]];

    CASE_EQUAL_LOGLEVEL(LogLevel::INFO);
    [[fallthrough]];

    CASE_EQUAL_LOGLEVEL(LogLevel::WARNING);
    [[fallthrough]];

    CASE_EQUAL_LOGLEVEL(LogLevel::ERROR);
    [[fallthrough]];

    CASE_EQUAL_LOGLEVEL(LogLevel::CRITICAL);
    break;

    default:
      // TODO: Handle error we have an uncovered LogLevel value
      break;
  }

  return false;
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
}; // namespace log
