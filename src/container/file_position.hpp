#ifndef AWX_CONTAINER_FILE_POSITION_HPP
#define AWX_CONTAINER_FILE_POSITION_HPP

// STL Includes:
#include <string>


struct FilePosition {
  // Members:
  std::string m_path;
  std::string m_line;

  std::size_t m_lineno;
  std::size_t m_columno;

  // Methods:
  FilePosition();
  FilePosition(std::string t_path, std::string t_line, std::size_t t_lineno,
               std::size_t t_columnno);

  friend auto operator<<(std::ostream& t_os, const FilePosition& t_fp)
    -> std::ostream&;

  virtual ~FilePosition() = default;
};

#endif // AWX_CONTAINER_FILE_POSITION_HPP
