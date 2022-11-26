#ifndef FILEBUFFER_H
#define FILEBUFFER_H

#include <vector>
#include <string>
#include <string_view>

#include "types.hpp"


class FileBuffer {
private:
  std::vector<std::string> m_file;

public:
  FileBuffer();
  // FileBuffer(std::string_view t_pathname);

  virtual ~FileBuffer();
};

#endif // FILEBUFFER_H
