#include "file_buffer.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>


// Constructors:

FileBuffer::FileBuffer()
{
  m_filebuffer.emplace_back("");
}

FileBuffer::FileBuffer(fs::path&& t_path)
  : m_path{std::move(t_path)}, m_lineno{0}, m_columnno{0}
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
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    // Dont discard newlines
    line += '\n';

    m_filebuffer.push_back(line);
  }
}

auto FileBuffer::next() const -> std::string
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_filebuffer[m_lineno++];
}

auto FileBuffer::prev() const -> std::string
{
  std::string result{m_filebuffer[m_lineno]};

  // Changing lines resets the column number
  m_columnno = 0;

  // Logically you can go past a stream but not in front of a stream
  if(m_lineno)
    m_lineno--;

  return result;
}

auto FileBuffer::forward() const -> char
{
  return m_filebuffer[m_lineno][m_columnno++];
}

auto FileBuffer::backward() const -> char
{
  const char character{m_filebuffer[m_lineno][m_columnno]};

  if(m_columnno)
    m_columnno--;

  return character;
}

auto FileBuffer::line() const -> std::string
{
  return m_filebuffer[m_lineno];
}

auto FileBuffer::character() const -> char
{
  return m_filebuffer[m_lineno][m_columnno];
}

auto FileBuffer::file_position() const -> FilePosition
{
  // Return the current position in the filebuffer as a FilePosition struct
  return {m_path.string(), m_filebuffer[m_lineno], m_lineno, m_columnno};
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
  return m_lineno >= size();
}

auto FileBuffer::path() const -> fs::path
{
  return m_path;
}

// Operators:
auto operator<<(std::ostream& t_os, const FileBuffer& t_fb) -> std::ostream&
{
  for(auto& line : t_fb.m_filebuffer) {
    t_os << line;
  }

  return t_os;
}
