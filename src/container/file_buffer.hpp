#ifndef AWX_CONTAINER_FILE_BUFFER_HPP
#define AWX_CONTAINER_FILE_BUFFER_HPP

// Includes:
#include "../types.hpp"

// Local Includes:
#include "text_buffer.hpp"


namespace container {
// Forward Declarations:
class FileBuffer;

// Aliases:
using FileBufferPtr = std::shared_ptr<FileBuffer>;

// Classes:
class FileBuffer : public TextBuffer {
  private:
  fs::path m_path;

  public:
  FileBuffer() = default;
  FileBuffer(fs::path&& t_path);

  auto load() -> void;
  auto path() const -> fs::path override;
  auto file_position() const -> FilePosition override;

  // Operators:
  friend auto operator<<(std::ostream& t_os, const FileBuffer& t_fb)
    -> std::ostream&;

  virtual ~FileBuffer() = default;
};
} // namespace container

#endif // AWX_CONTAINER_FILE_BUFFER_HPP
