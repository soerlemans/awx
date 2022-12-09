#include <iostream>

#include "parser/parser.hpp"
#include "lexer/token_type.hpp" // This was for enum2underlying_type function

#include "log.hpp"


auto print_help() -> void
{
  std::cout << "AWX - Help Manual\n"
			<< "Usage: awx <file>\n"
			<< "Flags:\n"
			<< " <-h> Displays this help manual\n"
			<< '\n';
}

auto run(int argc, char* argv[]) -> void
{
  // Set loglevel for now for debugging purposes
  SET_LOGLEVEL(LogLevel::DEBUG);

  FileBuffer fb{argv[1]};

  Lexer lexer{fb};
  TokenStream token_stream{lexer.tokenize()};

  Parser parser{token_stream};
  parser.parse();
}

auto main(int argc, char* argv[]) -> int
{
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
