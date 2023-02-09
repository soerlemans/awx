#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include "file_position.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

class FileBuffer {
  private:
  // Private variables:
  fs::path m_path;
  std::vector<std::string> m_filebuffer;

  // Keep track of current position in the filebuffer
  mutable std::size_t m_lineno, m_columnno;

  public:
  // Constructors:
  FileBuffer() = delete;
  FileBuffer(fs::path t_path);

  // Load and Save the FileBuffer from FS
  auto load() -> void;
  auto save() -> void; // TODO: Have this return an error code?

  auto path() const -> fs::path;

  // Line movement
  auto next() const -> std::string;
  auto prev() const -> std::string;

  // Character movement
  auto forward() const -> char;
  auto backward() const -> char;

  // Get current line
  auto line() const -> std::string;

  // Get current character
  auto character() const -> char;

  // Get indexes
  auto lineno() const -> std::size_t;
  auto columnno() const -> std::size_t;
  auto file_position() const -> FilePosition;

  auto size() const -> std::size_t;
  auto eol() const -> bool;
  auto eof() const -> bool;

  auto print() -> void;

  // Operators:
  auto operator[](std::size_t t_index) -> std::string&;

  // Destructors:
  virtual ~FileBuffer() = default;
};

#endif // FILE_BUFFER_H
