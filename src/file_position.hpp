#ifndef AWX_FILE_POSITION_HPP
#define AWX_FILE_POSITION_HPP

#include <string>

struct FilePosition {
  // Members:
  std::string m_path;
  std::string m_line;

  std::size_t m_lineno;
  std::size_t m_columno;

  // Constructors:
  FilePosition();
  FilePosition(std::string t_path, std::string t_line, std::size_t t_lineno,
               std::size_t t_columnno);

  // Operators:
  friend auto operator<<(std::ostream& t_os, const FilePosition& t_fp)
    -> std::ostream&;

  // Destructor:
  virtual ~FilePosition() = default;
};

#endif // AWX_FILE_POSITION_HPP
