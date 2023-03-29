#include "config.hpp"


// Static members:
std::unique_ptr<Config> Config::m_singleton;

// Protected methods:
auto Config::add_file(const fs::path& t_path) -> void
{
  m_paths.push_back(t_path);
}

// Public methods:
auto Config::get_files() const -> std::vector<fs::path>
{
  return m_paths;
}
