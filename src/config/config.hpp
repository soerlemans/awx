#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <memory>
#include <string>
#include <vector>


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

// Config store contains global configuration data like settings we pass from
// the command line or from a awx module settings file
// Note: This class is a singleton for now!
// If we ever allow per file configuration we should change this! To each file
// having its own config store object
// TODO: Have Config inherit from a singleton so we can just focus on protected
// Setters and public getters/etc
class Config {
  private:
  // Regular private variables:
  AwxMode m_awx_mode;
  std::vector<fs::path> m_file_paths;

  protected:
  static std::unique_ptr<Config> m_singleton;

  Config();

  auto add_path(fs::path&& t_path) -> void;

  public:
  // Constructors:
  Config(const Config&) = delete;

  // Public methods:
  static auto get_instance() -> Config&;

  auto get_paths() const -> std::vector<fs::path>;

  // Friend declarations:
  friend auto parse_args(const int t_argc, char* t_argv[]) -> void;

  // Operators:
  auto operator=(const Config&) -> Config& = delete;
};

#endif // CONFIG_H
