#include <exception>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "filebuffer.hpp"


// Constructors:
FileBuffer::FileBuffer(fs::path t_path)
  :m_path{t_path}
{
  m_filebuffer.reserve(256);

  load();
}

// Methods:
auto FileBuffer::load() -> void
{
  if(!fs::exists(m_path)) {
	std::string error_str{"File does not exist! \""};
	error_str += m_path.string();
	error_str += "\"";

	throw std::invalid_argument{error_str};
  }

  std::ifstream ifs{m_path};
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

// Operators:
auto FileBuffer::operator[](std::size_t t_index) -> std::string&
{
  return m_filebuffer[t_index];
}

auto FileBuffer::operator++() -> std::string&
{
  return m_filebuffer[m_lineno++];
}

auto FileBuffer::operator--() -> std::string&
{
  return m_filebuffer[m_lineno--];
}

// Destructor:
FileBuffer::~FileBuffer()
{}
