#include <functional>
#include <iostream>

#include <unistd.h>

#include "enum.hpp"
#include "config/config.hpp"
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
  std::cout << "AWX - Help Manual\n"
            << "Usage: awx <flags> '<awx program>'\n"
            << "Flags:\n"
            << " <-f program file> \n"
            << " <-h> Displays this help manual\n"
            << '\n';
}

// Parse command line arguments and store them in a configuration class
// Warning: This is friend of the ConfigStore class
auto parse_args(const int t_argc, char* t_argv[]) -> void
{
  auto& config{Config::get_instance()};

  const auto f_getopt{std::bind(getopt, t_argc, t_argv, "f:h")};
  for(auto option{f_getopt()}; option != -1; option = f_getopt())
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
}

auto run(int argc, char* argv[]) -> void
{
  // Set loglevel for now for debugging purposes
  SET_LOGLEVEL(log::LogLevel::DEBUG);

  auto& config{Config::get_instance()};

  // TODO: Remove this is temporary testing code
  if(!config.get_files().size())
    return;

  FileBuffer fb{config.get_files().front()};

  Lexer lexer{fb};
  TokenStream tokenstream{lexer.tokenize()};

  AwkParser parser{tokenstream};
  auto ast{parser.parse()};
}

auto main(int argc, char* argv[]) -> int
{
  parse_args(argc, argv);

  try {
    run(argc, argv);
  } catch(std::exception& e) {
    std::cerr << "EXCEPTION OCCURED - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
