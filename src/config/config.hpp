#ifndef AWX_CONFIG_CONFIG_HPP
#define AWX_CONFIG_CONFIG_HPP

// STL Includes:
#include <filesystem>
#include <list>
#include <memory>
#include <string>
#include <vector>

// Includes:
#include "../container/text_buffer.hpp"


// Aliases:
namespace fs = std::filesystem;

/*!The AWX mode determines the interpreters mode and what it considers valid
 * syntax and supported features
 */
enum AwxMode {
  POSIX_AWK = 0,   // Run as POSIX compatable AWK
  TRADITIONAL_AWK, // Run as Brian Kernighan's AWK
  AWK, // Allow AWX extensions but do not break backwards compatibility
  AWX, // Disregard all backwards compatibility and run as AWX interpreter
};

/*! The Config contains global data like options passed from the command line
 */
struct Config {
  AwxMode m_awx_mode;

  std::vector<std::string> m_scripts;
  std::list<std::string> m_args;

  Config(AwxMode t_awx_mode);
};

#endif // AWX_CONFIG_CONFIG_HPP
