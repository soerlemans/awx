#ifndef FILEBUFFER_H
#define FILEBUFFER_H

#include <filesystem>
#include <vector>
#include <string>
#include <string_view>

#include "types.hpp"

namespace fs = std::filesystem;

class FileBuffer {
private:

  std::vector<std::string> m_file;

public:
  FileBuffer();
  FileBuffer(std::string_view t_path);

  auto load_file(fs::path t_path) -> void;

  virtual ~FileBuffer();
};

#endif // FILEBUFFER_H
