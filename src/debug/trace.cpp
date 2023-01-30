#include "trace.hpp"

#include <cstddef>
#include <iomanip>
#include <sstream>


// Static variables:
int Trace::m_counter{0};

// Methods:
auto Trace::indent_text() const -> std::string
{
  std::stringstream ss;
  if(m_counter > 0) {
    ss << " " << std::string(m_counter, ' ');
  } else {
    ss << "#.";
  }

  ss << "─> ";

  return ss.str();
}

// Destructor:
Trace::~Trace()
{
  if(m_print) {
    m_counter--;
  }
}
