#include <iostream>

#include "filebuffer.hpp"
#include "parser.hpp"

auto print_help() -> void
{
  std::cout << "AWX - Help Manual\n"
			<< " <-h> Displays this help manual\n"
			<< '\n';
	}

int main(int argc, char *argv[])
{
  if (argc < 2)
	{
	  std::cout << "No arguments were given\n";
	  print_help();

	  return 0;
	}

  try {
	FileBuffer program{argv[1]};
  } catch(std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
  }

  return 0;
}
