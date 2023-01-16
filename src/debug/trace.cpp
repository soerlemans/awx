#include "trace.hpp"

#include <cstddef>
#include <sstream>


int Trace::m_counter{0};

Trace::Trace(log::LogLevel t_loglevel, std::string t_msg)
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
    ss << t_msg;

    LOG_PRINT(ss.str());
  }

  m_counter++;
}


Trace::~Trace()
{
  m_counter--;
}
