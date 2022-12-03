#include <iostream>

#include "tokenizer.hpp"
#include "parser.hpp"
#include "tokentype.hpp"

auto print_help() -> void
{
  std::cout << "AWX - Help Manual\n"
			<< "Usage: awx <file>"
			<< "Flags:"
			<< " <-h> Displays this help manual\n"
			<< '\n';
}

auto run(int argc, char* argv[]) -> void
{
  FileBuffer fb{argv[1]};
  Tokenizer tokenizer{fb};

  TokenStream token_stream{tokenizer.tokenize()};

  for(Token token : token_stream)
	{
	  std::cout << enum2underlying_type(token.type()) << '\n';
	}
}

int main(int argc, char* argv[])
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
