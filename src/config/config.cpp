#include "config.hpp"


// Static members:
std::unique_ptr<Config> Config::m_singleton;

// Protected constructors:
Config::Config(): m_awx_mode{AwxMode::AWK}, m_file_paths{}
{}

// Protected methods:
auto Config::add_path(fs::path&& t_path) -> void
{
  m_file_paths.push_back(std::forward<fs::path>(t_path));
}

// Public methods:
auto Config::get_paths() const -> std::vector<fs::path>
{
  return m_file_paths;
}
