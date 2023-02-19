#include <functional>
#include <iostream>

#include <unistd.h>

#include "config/config.hpp"
#include "enum.hpp"
#include "parser/awk_parser.hpp"

#include "debug/log.hpp"


// Enums:
enum ExitCode {
  OK = 0,
  EXCEPTION,
};

// Functions:
auto print_help() -> void
{
  // TODO: Implement [--]
  // TODO: Implement [File]
  std::cout << "Usage: awx [Options]\n"
            << "Options:\n"
            << "    -f program-file\n"
            << "    -h Displays this help manual\n"
            << "    -c Traditional mode\n"
            << '\n';
}

// NOLINTBEGIN
// Parse command line arguments and store them in a configuration class
// Warning: This is friend of the ConfigStore class
auto parse_args(const int t_argc, char* t_argv[]) -> void
{
  auto& config{Config::get_instance()};

  const auto f_getopt{[&] {
    return getopt(t_argc, t_argv, "f:h");
  }};

  if(auto option{f_getopt()}; option != -1) {
    for(; option != -1; option = f_getopt())
      switch(option) {
        case 'f': {
          config.add_file(fs::path{optarg});
          break;
        }

        case 'h':
        default:
          print_help();
          break;
      }
  } else {
    print_help();
  }
}

auto run(int argc, char* argv[]) -> void
{
  auto& config{Config::get_instance()};

  // TODO: Remove this is temporary testing code
  if(config.get_files().empty())
    return;

  FileBuffer fb{config.get_files().front()};

  Lexer lexer{fb};
  TokenStream tokenstream{lexer.tokenize()};

  AwkParser parser{tokenstream};
  auto ast{parser.parse()};
}
// NOLINTEND

auto main(int argc, char* argv[]) -> int
{
  // Set loglevel for now for debugging purposes
  SET_LOGLEVEL(log::LogLevel::DEBUG);
  LOG_PRINTLN("#== BEGIN ==#");

  parse_args(argc, argv);

  try {
    run(argc, argv);
  } catch(std::exception& e) {
    std::cerr << '\n' << "EXCEPTION OCCURED - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  LOG_PRINTLN("#== END ==#");

  return ExitCode::OK;
}
