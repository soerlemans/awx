#include "file_position.hpp"

// STL Includes:
#include <sstream>


using namespace container;

FilePosition::FilePosition(): m_path{""}, m_line{""}, m_lineno{0}, m_columno{0}
{}

// Its important to note that lines are zero indexed
FilePosition::FilePosition(std::string t_path, std::string t_line,
                           std::size_t t_lineno, std::size_t t_columnno)
  : m_path{std::move(t_path)},
    m_line{std::move(t_line)},
    m_lineno{t_lineno},
    m_columno{t_columnno}
{}

namespace container {
auto operator<<(std::ostream& t_os, const FilePosition& t_fp) -> std::ostream&
{
  std::stringstream ss;
  // To print the correct line number we have to increment by one since it is
  // Zero indexed
  ss << "Line(" << t_fp.m_lineno + 1 << "): ";
  const auto offset{ss.str().size() + t_fp.m_columno};

  t_os << "File: \"" << t_fp.m_path << "\"\n";
  t_os << ss.str() << t_fp.m_line;
  t_os << std::string(offset, ' ') << "^";

  return t_os;
}
} // namespace container
