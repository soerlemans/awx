#include "trace.hpp"

#include <cstddef>
#include <sstream>


// Static variables:
int Trace::m_counter{0};

// Methods:
auto Trace::indent_text() const -> std::string
{
  std::stringstream ss;
  ss << ((m_counter > 0) ? " ├" : "#.");

  // Adjust for the proper level of indentation
  for(int i{0}; i < m_counter - 1; i++)
    ss << "─";

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
