#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string_view>

#include "../types.hpp"

// Only log if we are on the development build
#if DEVELOPMENT

// Macros:
#define LOG_PRINTLN(...) log::println(__VA_ARGS__)

#define LOG(loglevel, ...) \
  log::log(__FILE__, __func__, __LINE__, log::loglevel, __VA_ARGS__)

#define SET_LOGLEVEL(loglevel) set_loglevel(loglevel)

#else

// Stub the macros if we are not on the debugging build
#define LOG_PRINTLN(...) \
  do {                   \
  } while(0)

#define LOG(...) \
  do {           \
  } while(0)

#define SET_LOGLEVEL(level) \
  do {                      \
  } while(0)

#endif // DEBUG

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

#if DEVELOPMENT
// Functions:
auto is_lower_loglevel(LogLevel t_loglevel) -> bool;
constexpr auto loglevel2str(LogLevel t_loglevel) -> std::string_view;
auto set_loglevel(LogLevel t_loglevel) -> void;

// We use std::clog for logging
template<typename... Args>
auto print(Args&&... t_args) -> void
{
  // Fold expression
  (std::clog << ... << t_args);
}

template<typename... Args>
auto println(Args&&... t_args) -> void
{
  // Fold expression
  print(std::forward<Args>(t_args)..., '\n');
}

// Do not use this function with non primitive types it will not know how to
// Handle them and give an obscure tuple error
// TODO: Maybe inline log? We will be using it a lot for debugging
template<typename... Args>
auto log(std::string_view t_file, std::string_view t_function, int t_lineno,
         LogLevel t_loglevel, Args&&... t_args) -> void
{
  // Ignore higher log levels
  if(is_lower_loglevel(t_loglevel)) {
    // Denote loglevel
    print('[', loglevel2str(t_loglevel), ']');

    // Module information
    print('[', t_file, ':', t_lineno, " -> ", t_function, "()] => ");

    // Log what we want to log
    println(std::forward<Args>(t_args)...);
  }
}

#endif // DEBUG
} // namespace log
#endif // LOG_HPP
