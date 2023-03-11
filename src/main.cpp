// STL Includes:
#include <functional>
#include <iostream>

// Library Includes:
#include <CLI/CLI.hpp>

// Includes:
#include "config/config.hpp"
#include "debug/log.hpp"
#include "parser/awk_parser.hpp"

// Local Includes:
#include "enum.hpp"

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

auto run() -> void
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

auto main(int t_argc, char* t_argv[]) -> int
{
  CLI::App app{"AWX is a POSIX AWK implementation with extensions."};

  std::string filename = "default";
  app.add_option("-f,--file", filename, "A help string");

  CLI11_PARSE(app, t_argc, t_argv);

  // Set loglevel for now for debugging purposes
  DBG_SET_LOGLEVEL(VERBOSE);
  DBG_PRINTLN("#== BEGIN ==#");

  // parse_args(t_argc, t_argv);

  try {
    run();
  } catch(std::exception& e) {
    std::cerr << '\n' << "EXCEPTION OCCURED - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  DBG_PRINTLN("#== END ==#");

  return ExitCode::OK;
}
