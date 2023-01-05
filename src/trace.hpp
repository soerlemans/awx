#ifndef TRACE_H
#define TRACE_H

#include "log.hpp"


// Trace class used for figuring out
class log::Trace {
private:
  static unsigned int m_counter;

public:
  Trace();

  virtual ~Trace();
};


#endif // TRACE_H
