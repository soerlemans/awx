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
  std::size_t m_lineno{0}, m_columnno{0};
  std::vector<std::string> m_filebuffer;

public:
  FileBuffer();
  FileBuffer(std::string_view t_path);

  auto load_file(fs::path t_path) -> void;

  auto print(bool t_all=false) -> void;

  virtual ~FileBuffer();
};

#endif // FILEBUFFER_H
