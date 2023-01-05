#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string_view>

#include "../types.hpp"


namespace log {
// Enums:
// Different logging levels
enum class LogLevel : u16 {
  CRITICAL = 0,
  ERROR,
  WARNING,
  INFO,
  DEBUG,
};

// Only log if we are on the development build
#if DEVELOPMENT

// Macros:
#define PRINT(...) log::print(__VA_ARGS__)

#define LOG(loglevel, ...) \
  log::log(__FILE__, __FUNCTION__, __LINE__, log::loglevel, __VA_ARGS__)

#define SET_LOGLEVEL(loglevel) set_loglevel(loglevel)

// Functions:
template<typename... Args>
auto print(Args&&... t_args) -> void
{
  // Fold expression
  (std::clog << ... << t_args) << '\n';
}

auto is_lower_loglevel(const LogLevel t_loglevel) -> bool;
auto loglevel2str(const LogLevel t_loglevel) -> std::string_view;
auto set_loglevel(const LogLevel t_loglevel) -> void;

// Do not use this function with non primitive types it will not know how to
// Handle them and give an obscure tuple error
// TODO: Maybe inline log? We will be using it a lot for debugging
template<typename... Args>
auto log(std::string_view t_file, std::string_view t_function, int t_lineno,
         LogLevel t_loglevel, Args&&... t_args) -> void
{
  // Ignore higher log levels
  if(!is_lower_loglevel(t_loglevel))
    return;

  // Denote loglevel
  std::clog << '[' << loglevel2str(t_loglevel) << ']';

  // Module information
  std::clog << '[' << t_file << ':' << t_lineno << " -> " << t_function
            << "()] => ";

  print(std::forward<Args>(t_args)...);
}

#else

// Stub the macros if we are not on the debugging build
#define PRINT(...) \
  do {             \
  } while(0)

#define LOG(...) \
  do {           \
  } while(0)

#define SET_LEVEL(level) \
  do {                   \
  } while(0)

#endif // DEBUG
#endif // LOG_H
};
