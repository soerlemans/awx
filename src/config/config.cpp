#include "config.hpp"
#include <memory>


// Static members:
std::unique_ptr<Config> Config::m_singleton;

// Private Constructors:
Config::Config()
  : m_awx_mode{AwxMode::AWK}, m_file_paths{}
{}

auto Config::add_path(fs::path&& t_path) -> void
{
  m_file_paths.push_back(std::forward<fs::path>(t_path));
}

// Public methods:
auto Config::get_instance() -> Config&
{
  if(!m_singleton)
    m_singleton = std::unique_ptr<Config>(new Config);

  return *(m_singleton.get());
}

auto Config::get_paths() const -> std::vector<fs::path>
{
  return m_file_paths;
}
