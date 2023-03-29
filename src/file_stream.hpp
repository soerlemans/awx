#ifndef FILE_STREAM_HPP
#define FILE_STREAM_HPP

// STL Includes:
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

// Local Includes:
#include "stream.hpp"

namespace fs = std::filesystem;

//! Filestream loads an entire file in as a sequential
class FileStream : public Stream<std::string> {
  private:
  public:
  FileStream(fs::path t_path);
};

#endif // FILE_STREAM_HPP
