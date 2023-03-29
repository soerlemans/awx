#include "file_stream.hpp"

// STL Includes:
#include <fstream>
#include <sstream>


FileStream::FileStream(fs::path t_path)
{
  std::ifstream ifs(t_path);
  std::stringstream ss;

  // Read in the entire file as a string
  ss << ifs.rdbuf();

  this->assign(ss.str());
}
