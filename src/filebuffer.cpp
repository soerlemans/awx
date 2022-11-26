#include <exception>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "filebuffer.hpp"

FileBuffer::FileBuffer()
{
  m_filebuffer.reserve(256);
}

FileBuffer::FileBuffer(std::string_view t_path)
{
  m_filebuffer.reserve(256);

  load_file(t_path);
}

auto FileBuffer::load_file(fs::path t_path) -> void
{
  if(!fs::exists(t_path)) {
	std::string error_str{"File does not exist! \""};
	error_str += t_path.string();
	error_str += "\"";

	throw std::invalid_argument{error_str};
  }

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof())
	{
	  std::string line;
	  std::getline(ifs, line);

	  m_filebuffer.push_back(line);
	}
}

auto FileBuffer::print(bool t_all) -> void
{
  if (t_all) {
	for (const auto& line : m_filebuffer) {
	  std::cout << line << '\n';
		}
  } else {
	std::cout << "Line(" << m_lineno << "): " << m_filebuffer[m_lineno] << '\n';
  }
}

FileBuffer::~FileBuffer()
{

}
