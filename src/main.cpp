#include <iostream>

#include <unistd.h>

#include "parser/parser.hpp"
#include "lexer/token_type.hpp" // This was for enum2underlying_type function

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
auto parse_args(int t_argc, char* argv[]) -> void
{
  for(;;)
	{
	  const auto opt = getopt(argc, argv, "f");
	  switch(opt)
		{
		case 'f':
		  // handle the chosen program file
		  break;

		default:
		  return; // Quit function
		  break;
		}
	}
}

auto run(int argc, char* argv[]) -> void
{
  // Set loglevel for now for debugging purposes
  SET_LOGLEVEL(LogLevel::DEBUG);

  FileBuffer fb{argv[1]};

  Lexer lexer{fb};
  TokenStream token_stream{lexer.tokenize()};

  Parser parser{token_stream};
  auto ast{parser.parse()};
}

auto main(int argc, char* argv[]) -> int
{
  parse_args(argc, argv);

  // TODO: Use getopt for argument parsing
  if (argc < 2)
	{
	  std::cout << "No arguments were given\n";
	  print_help();

	  return 0;
	}

  try {
	run(argc, argv);
  } catch(std::exception& e) {
	std::cout << e.what() << '\n';

	return 1;
  }

  return 0;
}
