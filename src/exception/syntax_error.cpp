#include "syntax_error.hpp"

#include <iomanip>
#include <sstream>
#include <string>

// The following members m_lineno and m_columno are zero indexed so they need to
// Have + 1 counted for them to line up properly
SyntaxError::SyntaxError(std::string t_msg, std::string t_path,
                         std::size_t t_lineno, std::string t_line,
                         std::size_t t_columnno)
  : m_error{},
    m_path{t_path},
    m_lineno{t_lineno + 1},
    m_line{t_line},
    m_columnno(t_columnno + 1)
{
  std::stringstream ss;
  std::stringstream lineno_ss;

  lineno_ss << " - Line(";
  lineno_ss << t_lineno;
  lineno_ss << "): ";

  ss << "Error in file: " << '"' << t_path << '"' << '\n';
  ss << "Error description: " << '"' << t_msg << '"' << "\n";
  ss << lineno_ss.str();

  // FIXME: If t_line does not end in a newline we have an issue!
  ss << t_line;

  // FIXME: ~^~ does not align
  const auto indent{lineno_ss.str().size() + m_columnno};
  ss << std::setw(indent) << "~^~" << '\n';

  m_error = ss.str();
}

auto SyntaxError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
