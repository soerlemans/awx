#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "filebuffer.hpp"


// Constructors:
FileBuffer::FileBuffer(fs::path t_path)
  : m_path{t_path}, m_lineno{0}, m_columnno{0}
{
  m_filebuffer.reserve(256);

  load();
}

// Methods:
auto FileBuffer::load() -> void
{
  if(!fs::exists(m_path))
    {
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

auto FileBuffer::path() const -> fs::path
{
  return m_path;
}

auto FileBuffer::next() -> std::string&
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_filebuffer[m_lineno++];
}

auto FileBuffer::prev() -> std::string&
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_filebuffer[m_lineno--];
}

auto FileBuffer::next() const -> std::string
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_filebuffer[m_lineno++];
}

auto FileBuffer::prev() const -> std::string
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_filebuffer[m_lineno--];
}

auto FileBuffer::forward() const -> char
{
  return m_filebuffer[m_lineno][m_columnno++];
}

auto FileBuffer::backward() const -> char
{
  return m_filebuffer[m_lineno][m_columnno--];
}

auto FileBuffer::line() -> std::string&
{
  return m_filebuffer[m_lineno];
}

auto FileBuffer::line() const -> std::string
{
  return m_filebuffer[m_lineno];
}

auto FileBuffer::character() const -> char
{
  return m_filebuffer[m_lineno][m_columnno];
}

auto FileBuffer::lineno() const -> std::size_t
{
  return m_lineno;
}

auto FileBuffer::columnno() const -> std::size_t
{
  return m_columnno;
}

auto FileBuffer::begin() -> File::iterator
{
  return m_filebuffer.begin();
}

auto FileBuffer::end() -> File::iterator
{
  return m_filebuffer.end();
}

auto FileBuffer::size() const -> std::size_t
{
  return m_filebuffer.size();
}

auto FileBuffer::eol() const -> bool
{
  return m_columnno >= line().size();
}

auto FileBuffer::eof() const -> bool
{
  if(m_lineno >= m_filebuffer.size())
    if(m_columnno >= line().size())
      {
        return true;
    }

  return false;
}

auto FileBuffer::print(bool t_all) -> void
{
  if(t_all)
    {
      for(const auto& line : m_filebuffer)
        {
          std::cout << line << '\n';
        }
  } else
    {
      std::cout << "Line(" << m_lineno << "): " << m_filebuffer[m_lineno]
                << '\n';
    }
}

// Operators:
auto FileBuffer::operator[](std::size_t t_index) -> std::string&
{
  return m_filebuffer[t_index];
}

// Destructor:
FileBuffer::~FileBuffer()
{}
