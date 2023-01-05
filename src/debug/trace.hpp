#ifndef TRACE_H
#define TRACE_H

#include "log.hpp"


// Only facilitate trace if we are on DEVELOPMENT build
#if DEVELOPMENT

// Helper macros for TRACE:
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

// TRACE is intended for showing which functions call which in a tree like
// manner
#define TRACE(loglevel, str)       \
  Trace CONCAT(trace, __COUNTER__) \
  {                                \
    log::loglevel, str             \
  }

// Trace class used for figuring out
class Trace {
  private:
  static int m_counter;

  public:
  Trace(log::LogLevel t_loglevel, std::string t_msg);

  virtual ~Trace();
};

#else

#define TRACE(str) \
  do {             \
  } while(0)

#define TRACE_END(str) \
  do {                 \
  } while(0)

#endif // DEBUG
#endif // TRACE_H
