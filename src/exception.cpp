#include <sstream>
#include <string>

#include "exception.hpp"


// The following members m_lineno and m_columno
// Are zero indexed so they need to have + 1 counted for them to line up properly
SyntaxError::SyntaxError(std::string t_msg, std::size_t t_lineno,
                         std::string t_line, std::size_t t_columnno)
  :m_error{}, m_lineno{t_lineno + 1}, m_line{t_line}, m_columnno(t_columnno + 1)
{
  std::stringstream ss;
  std::string line_str{" - Line("};

  line_str += std::to_string(t_lineno);
  line_str += "): ";

  auto pos{line_str.size() + m_columnno};
  std::string column_str(pos, ' ');

  ss << '"' << t_msg << "\"\n";
  ss << line_str;
  ss << t_line << '\n';

  // Use the temp string to point where the error was found
  // FIXME: The ^^^ does not properly align
  ss << column_str << "^^^" << '\n';

  m_error = ss.str();
}

auto SyntaxError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
