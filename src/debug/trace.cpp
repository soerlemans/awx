#include "trace.hpp"


int Trace::m_counter{0};

Trace::~Trace()
{
  m_counter--;
}
