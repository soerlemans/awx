#ifndef FILE_BUFFER_HPP
#define FILE_BUFFER_HPP

// STL Includes:
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

// Local Includes:
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
  FileBuffer() = delete;
  FileBuffer(fs::path&& t_path);

  auto load() -> void;

  // Line movement
  auto next() const -> std::string;
  auto prev() const -> std::string;

  // Character movement
  auto forward() const -> char;
  auto backward() const -> char;

  auto line() const -> std::string;
  auto character() const -> char;

  auto file_position() const -> FilePosition;

  auto size() const -> std::size_t;

  auto eol() const -> bool;
  auto eof() const -> bool;

  virtual ~FileBuffer() = default;
};

#endif // FILE_BUFFER_HPP
