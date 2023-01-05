#ifndef TRACE_H
#define TRACE_H

#include "log.hpp"


// Only log if we are on the development build
#if DEVELOPMENT

// Helper macros for TRACE:
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

// TRACE is intended for presenting readable stack traces
#define TRACE(str)                 \
  Trace CONCAT(trace, __COUNTER__) \
  {                                \
    str                            \
  }


// Trace class used for figuring out
class Trace {
  private:
  static unsigned int m_counter;

  public:
  Trace();

  virtual ~Trace();
};

#else

#define TRACE() \
  do {          \
  } while(0)

#endif // DEBUG
#endif // TRACE_H
