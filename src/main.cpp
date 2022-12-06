#include <iostream>

#include "expression.hpp"
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

  Lexer lexer{fb};
  TokenStream token_stream{lexer.tokenize()};

  Parser parser{token_stream};
  parser.parse();

  // FIXME: Does not work???
  Expression expr{TokenType::FUNCTION_KEYWORD, Expression{TokenType::DO_KEYWORD}};


  for(Token& token : token_stream)
	{
	  std::cout << enum2underlying_type(token.type()) << '\n';
	}
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
