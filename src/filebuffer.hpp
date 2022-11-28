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
  fs::path m_path;
  std::size_t m_lineno{0}, m_columnno{0};
  std::vector<std::string> m_filebuffer;

public:
  FileBuffer() = delete;
  FileBuffer(fs::path t_path);

  auto load() -> void;
  auto save() -> void; // TODO: Have this return an error code?

  auto line() -> std::string&;
  auto lineno() const -> std::size_t;
  auto columnno() const -> std::size_t;

  auto begin() -> std::vector<std::string>::iterator;
  auto end() -> std::vector<std::string>::iterator;

  auto size() const -> std::size_t;

  auto print(bool t_all=false) -> void;

  // Operators:
  auto operator[](std::size_t t_index) -> std::string&;
  auto operator++(int) -> std::string;
  auto operator--(int) -> std::string;

  virtual ~FileBuffer();
};

#endif // FILEBUFFER_H
