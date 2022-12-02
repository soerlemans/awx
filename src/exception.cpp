#include <sstream>
#include <string>

#include "exception.hpp"


// The following members m_lineno and m_columno are zero indexed so they need to
// Have + 1 counted for them to line up properly
SyntaxError::SyntaxError(std::string t_msg, std::string t_path,
                         std::size_t t_lineno, std::string t_line,
                         std::size_t t_columnno)
:m_error{}, m_path{t_path}, m_lineno{t_lineno + 1}, m_line{t_line}, m_columnno(t_columnno + 1)
{
  std::stringstream ss;
  std::stringstream columnno_ss;

  columnno_ss << " - Line(";
  columnno_ss << t_lineno;
  columnno_ss << "): ";

  ss << '"' << t_msg << "\"\n";
  ss << columnno_ss.str();
  ss << t_line << '\n';

  const auto pos{columnno_ss.str().size() + m_columnno};
  std::string column_str(pos, ' ');

  // Use the temp string to point where the error was found
  // FIXME: The ^^^ does not properly align
  ss << column_str << "^^^" << '\n';

  m_error = ss.str();
}

auto SyntaxError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
