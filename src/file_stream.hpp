#ifndef FILE_STREAM_HPP
#define FILE_STREAM_HPP

// STL Includes:
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

// Local Includes:
#include "stream.hpp"

//! Filestream loads an entire file in as a sequential
class FileStream : public Stream<std::string> {
  private:
  namespace fs = std::filesystem;

  public:
};

#endif // FILE_STREAM_HPP
