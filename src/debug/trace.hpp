#ifndef TRACE_H
#define TRACE_H

#include <cstddef>
#include <sstream>

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
  static int m_counter;

  public:
  template<typename... Args>
  Trace(log::LogLevel t_loglevel, Args&&... t_args)
  {
    if(log::is_lower_loglevel(t_loglevel)) {
      std::stringstream ss;
      if(m_counter > 0) {
        ss << " ├";
      } else {
        ss << "#.";
      }

      // Adjust for the proper level of indentation
      for(int i{0}; i < m_counter - 1; i++)
        ss << "─";

      ss << "─> ";

      LOG_PRINT(ss.str(), std::forward<Args>(t_args)...);
    }

    m_counter++;
  }

  virtual ~Trace();
};

#else

#define TRACE(loglevel, ...) \
  do {                       \
  } while(false)

#define TRACE_PRINT(loglevel, ...) \
  do {                             \
  } while(false)

#endif // DEBUG
#endif // TRACE_H
