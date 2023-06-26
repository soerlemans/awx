#ifndef AWX_CONTAINER_FILE_BUFFER_HPP
#define AWX_CONTAINER_FILE_BUFFER_HPP

// STL Includes:
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

// Includes:
#include "../types.hpp"

// Local Includes:
#include "file_position.hpp"
#include "text_buffer.hpp"


namespace container {
// Forward Declarations:
class FileBuffer;

// Aliases:
namespace fs = std::filesystem;

// Classes:
class FileBuffer : public TextBuffer {
  private:
  fs::path m_path;

  public:
  FileBuffer() = default;
  FileBuffer(fs::path&& t_path);

  auto load() -> void;
  auto file_position() const -> FilePosition;
  auto path() const -> fs::path;

  // Operators:
  friend auto operator<<(std::ostream& t_os, const FileBuffer& t_fb)
    -> std::ostream&;

  virtual ~FileBuffer() = default;
};
} // namespace container

#endif // AWX_CONTAINER_FILE_BUFFER_HPP
