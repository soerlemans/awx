#include "log.hpp"


// Macros:
#define CHECK_LEVEL(loglevel)      \
  case loglevel:                   \
    do {                           \
        if(g_loglevel == loglevel) \
          {                        \
            return true;           \
        }                          \
    } while(0)

namespace {
// Private variables:
LogLevel g_loglevel{LogLevel::WARNING};
}; // namespace

// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
auto is_lower_loglevel(const LogLevel t_loglevel) -> bool
{
  switch(g_loglevel)
    {
      // These macros use the return statement
      CHECK_LEVEL(LogLevel::DEBUG);
      [[fallthrough]];

      CHECK_LEVEL(LogLevel::INFO);
      [[fallthrough]];

      CHECK_LEVEL(LogLevel::WARNING);
      [[fallthrough]];

      CHECK_LEVEL(LogLevel::ERROR);
      [[fallthrough]];

      CHECK_LEVEL(LogLevel::CRITICAL);
      break;

      default:
        // TODO: Handle error we have an uncovered LogLevel value
        break;
    }

  return false;
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}
