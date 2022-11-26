#include <exception>
#include <fstream>
#include <stdexcept>

#include "filebuffer.hpp"

FileBuffer::FileBuffer()
{

}

FileBuffer::FileBuffer(std::string_view t_path)
{
  load_file(t_path);
}

auto FileBuffer::load_file(fs::path t_path) -> void
{
  if(!fs::exists(t_path))
	throw std::invalid_argument{"File not found"};

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof())
	{
	  
	}
}

FileBuffer::~FileBuffer()
{

}
