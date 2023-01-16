#include "config.hpp"


// Static members:
std::unique_ptr<Config> Config::m_singleton;

// Protected constructors:
Config::Config(): m_awx_mode{AwxMode::AWK}, m_file_buffers{}
{}

// Protected methods:
auto Config::add_file(FileBuffer&& t_fb) -> void
{
  m_file_buffers.push_back(std::forward<FileBuffer>(t_fb));
}

// Public methods:
auto Config::get_files() const -> std::vector<FileBuffer>
{
  return m_file_buffers;
}
