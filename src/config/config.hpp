#ifndef CONFIG_HPP
#define CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

// Includes:
#include "../file_buffer.hpp"


namespace fs = std::filesystem;

// The AWX mode determines the interpreters mode and what it considers valid
// syntax and supported features
enum AwxMode {
  // Function strictly as POSIX compatible AWK interpreter
  AWK_STRICT = 0,

  // Be backwards compatible with AWK and allow AWX extensions, that do not
  // break backwards compatibility
  AWK,

  // Disregard all backwards compatibility and run as AWX interpreter
  AWX,
};

/*! Config store contains global configuration data like settings we pass from
 * the command line or from a awx module settings file
 */
struct Config {
  AwxMode m_awx_mode;
  std::string_view m_version;

  std::vector<std::string> m_paths;
  std::vector<std::string> m_filepaths;

  Config(AwxMode t_awx_mode, std::string_view t_version);
};

#endif // CONFIG_HPP
