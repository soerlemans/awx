#ifndef TRACE_H
#define TRACE_H

#include <string>

#include "log.hpp"


// Only facilitate trace if we are on DEVELOPMENT build
#if DEVELOPMENT

// Helper macros for TRACE:
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

// TRACE is intended for showing which functions call which in a tree like
// manner
#define TRACE(loglevel, ...)       \
  Trace CONCAT(trace, __COUNTER__) \
  {                                \
    log::loglevel, __VA_ARGS__     \
  }

// Creates a trace object in an enclosed scope, usefull for printing TRACE info
// on the same level within a function
#define TRACE_PRINT(loglevel, ...)                                \
  do {                                                            \
    Trace CONCAT(trace, __COUNTER__){log::loglevel, __VA_ARGS__}; \
  } while(false)

// Trace class used for figuring out
class Trace {
  private:
  // Counter that denotes the indent level
  static int m_counter;

  // Denotes if the message should be printed?
  bool m_print;

  public:
  template<typename... Args>
  Trace(log::LogLevel t_loglevel, Args&&... t_args)
    : m_print{log::is_lower_loglevel(t_loglevel)}
  {
    if(m_print) {
      LOG_PRINT(indent_text(), std::forward<Args>(t_args)..., " - (", m_counter,
                ')');

      m_counter++;
    }
  }

  virtual auto indent_text() const -> std::string;

  virtual ~Trace();
};

#else

// Stub the macros if we are not on the debugging build
#define TRACE(loglevel, ...) \
  do {                       \
  } while(false)

#define TRACE_PRINT(loglevel, ...) \
  do {                             \
  } while(false)

#endif // DEBUG
#endif // TRACE_H
