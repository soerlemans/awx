#include "config.hpp"


Config::Config(const AwxMode t_awx_mode, const std::string_view t_version)
  : m_awx_mode{t_awx_mode}, m_version{t_version}
{}
