#include <iostream>

#include "filebuffer.hpp"
#include "parser.hpp"


auto print_help() -> void
{
  std::cout << "AWX - Help Manual\n"
			<< " <-h> Displays this help manual\n"
			<< '\n';
}

auto run(int argc, char* argv[]) -> void
{
  FileBuffer fb{argv[1]};
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
	std::cout << "Error: " << e.what() << '\n';

	return 1;
  }

  return 0;
}
