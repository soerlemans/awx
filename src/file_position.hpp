#ifndef FILE_POSITION_H
#define FILE_POSITION_H

#include <string>

struct FilePosition {
  public:
  std::string m_path;
  std::string m_line;

  std::size_t m_lineno;
  std::size_t m_columno;

  public:
  // Constructors:
  FilePosition() = default;
  FilePosition(std::string t_path, std::string t_line, std::size_t t_lineno,
               std::size_t t_columnno);

  // Operators:
  friend auto operator <<(std::ostream& t_os, const FilePosition& t_fp) -> std::ostream&;

  // Destructor:
  virtual ~FilePosition();
};

#endif // FILE_POSITION_H
