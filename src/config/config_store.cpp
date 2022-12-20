#include "config_store.hpp"
#include <memory>


// Static members:
std::unique_ptr<ConfigStore> ConfigStore::m_singleton;

// Private Constructors:
ConfigStore::ConfigStore()
  : m_awx_mode{AwxMode::AWK}, m_file_paths{}
{}

auto ConfigStore::add_path(fs::path&& t_path) -> void
{
  m_file_paths.push_back(std::forward<fs::path>(t_path));
}

// Public methods:
auto ConfigStore::get_instance() -> ConfigStore&
{
  if(!m_singleton)
    m_singleton = std::unique_ptr<ConfigStore>(new ConfigStore);

  return *(m_singleton.get());
}

auto ConfigStore::get_paths() const -> std::vector<fs::path>
{
  return m_file_paths;
}
