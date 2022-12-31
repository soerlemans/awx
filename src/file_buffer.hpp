#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include "types.hpp"

namespace fs = std::filesystem;

class FileBuffer
{
  private:
  // Alisases:
  using File = std::vector<std::string>;

  // Private variables:
  fs::path m_path;
  mutable std::size_t m_lineno, m_columnno;
  File m_filebuffer;

  public:
  FileBuffer() = delete;
  FileBuffer(fs::path t_path);

  // Load and Save the FileBuffer from FS
  auto load() -> void;
  auto save() -> void; // TODO: Have this return an error code?

  auto path() const -> fs::path;

  // Line movement
  auto next() -> std::string&;
  auto prev() -> std::string&;

  auto next() const -> std::string;
  auto prev() const -> std::string;

  // Character movement
  auto forward() const -> char;
  auto backward() const -> char;

  // Get current line
  auto line() -> std::string&;
  auto line() const -> std::string;

  // Get current character
  auto character() const -> char;

  // Get indexes
  auto lineno() const -> std::size_t;
  auto columnno() const -> std::size_t;

  auto begin() -> File::iterator;
  auto end() -> File::iterator;

  auto size() const -> std::size_t;
  auto eol() const -> bool;
  auto eof() const -> bool;

  auto print() -> void;

  // Operators:
  auto operator[](std::size_t t_index) -> std::string&;

  // Destructors
  virtual ~FileBuffer();
};


#endif // FILE_BUFFER_H
