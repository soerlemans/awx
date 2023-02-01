#include "file_position.hpp"

#include <sstream>


FilePosition::FilePosition(std::string t_path, std::string t_line,
                           std::size_t t_lineno, std::size_t t_columnno)
  : m_path{std::move(t_path)},
    m_line{std::move(t_line)},
    m_lineno{t_lineno},
    m_columno{t_columnno}
{}

//Friend function:
auto operator<<(std::ostream& t_os, const FilePosition& t_fp) -> std::ostream&
{
  std::stringstream ss;
  ss << "Line(" << t_fp.m_lineno << "): " << t_fp.m_line;
  const auto offset{ss.str().size() + t_fp.m_columno};

  t_os << "File: \"" << t_fp.m_path << "\"\n";
  t_os << ss.str();
  t_os << std::string(offset, ' ') << "~^~";

  return t_os;
}

// Destructor:
FilePosition::~FilePosition()
{}
