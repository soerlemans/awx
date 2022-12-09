#include "log.hpp"


// Macros:
// TODO: THe break statement now leaves the do while loop this is not intended
#define CHECK_LEVEL(loglevel)      \
  case loglevel:                   \
    do                             \
      {                            \
        if(g_loglevel == loglevel) \
          {                        \
            is_lower = true;       \
            break;                 \
        }                          \
    } while(0)

namespace {
// Private variables:
LogLevel g_loglevel{LogLevel::WARNING};
}; // namespace

// Public functions:
// This function checks if the LogLevel is lower than the current g_loglevel
auto is_lower_loglevel(LogLevel t_loglevel) -> bool
{
  bool is_lower{false};
  switch(t_loglevel)
    {
      // These macros alter is_lower and [[fallthrough]]
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

  return is_lower;
}

auto set_loglevel(const LogLevel t_loglevel) -> void
{
  g_loglevel = t_loglevel;
}
