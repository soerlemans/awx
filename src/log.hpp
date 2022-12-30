#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string_view>

#include "types.hpp"


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
#define LOG(loglevel, ...) \
  log(__FILE__, __FUNCTION__, __LINE__, loglevel, __VA_ARGS__)

#define SET_LOGLEVEL(loglevel) set_loglevel(loglevel)

// Functions:
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

  // Fold expression
  (std::clog << ... << t_args) << '\n';
}

#else

// Stub the macros if we are not on the debugging build
#define LOG(...) \
  do {           \
  } while(0)
#define SET_LEVEL(level) \
  do {                   \
  } while(0)
#endif // DEBUG
#endif // LOG_H
