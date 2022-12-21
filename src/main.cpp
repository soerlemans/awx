#include <functional>
#include <iostream>

#include <unistd.h>

#include "config/config.hpp"
#include "parser/parser.hpp"

#include "log.hpp"


auto print_help() -> void
{
  std::cout << "AWX - Help Manual\n"
            << "Usage: awx <flags> <file>\n"
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
  for(auto opt{f_getopt()}; opt != -1; opt = f_getopt())
    switch(opt)
      {
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
  SET_LOGLEVEL(LogLevel::DEBUG);

  auto& config{Config::get_instance()};

  // TODO: REmove this is temporary testing code
  if(!config.get_files().size())
	return;

  FileBuffer fb{config.get_files().front()};

  Lexer lexer{fb};
  TokenStream token_stream{lexer.tokenize()};

  Parser parser{token_stream};
  auto ast{parser.parse()};
}

auto main(int argc, char* argv[]) -> int
{
  parse_args(argc, argv);

  try
    {
      run(argc, argv);
  } catch(std::exception& e)
    {
      std::cout << e.what() << '\n';

      return 1;
  }

  return 0;
}
