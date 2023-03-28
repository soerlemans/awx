// STL Includes:
#include <functional>
#include <iostream>

// Library Includes:
#include <CLI/CLI.hpp>

// Includes:
#include "config/config.hpp"
#include "debug/log.hpp"
#include "file_buffer.hpp"
#include "parser/awk_parser.hpp"
#include "visitor/print_visitor.hpp"
#include "visitor/tree_walk_interpreter.hpp"

// Local Includes:
#include "enum.hpp"

// Enums:
enum ExitCode {
  OK = 0,
  SIGNAL,
  EXCEPTION,
};

// Functions:
// NOLINTBEGIN
// Parse command line arguments and store them in a configuration class
// Warning: This is friend of the ConfigStore class
auto parse_args(const int t_argc, char* t_argv[]) -> int
{
  auto& config{Config::get_instance()};

  CLI::App app{"AWX stands for AWK With Extensions."};

  std::string filename;
  app.add_option("-f,--file", filename, "A help string");

  CLI11_PARSE(app, t_argc, t_argv);

  std::cout << filename << std::endl;
  config.add_file(fs::path{filename});

  return ExitCode::OK;
}
// NOLINTEND

auto run() -> void
{
  auto& config{Config::get_instance()};

  // TODO: Remove this is temporary testing code
  if(config.get_files().empty())
    return;

  FileBuffer fb{config.get_files().front()};

  Lexer lexer{fb};
  token::TokenStream tokenstream{lexer.tokenize()};

  parser::AwkParser parser{tokenstream};
  node::NodePtr ast{parser.parse()};

  // Pretty print ast
  visitor::PrintVisitor pretty_printer;
  ast->accept(&pretty_printer);

  // Execute program via tree walk interpreter
  DBG_PRINTLN("#== EXECUTING ==#");
  visitor::TreeWalkInterpreter interpreter;
  ast->accept(&interpreter);
}

auto main(int t_argc, char* t_argv[]) -> int
{
  parse_args(t_argc, t_argv);

  // Set loglevel for now for debugging purposes
  DBG_SET_LOGLEVEL(VERBOSE);
  DBG_PRINTLN("#== BEGIN ==#");

  try {
    run();
  } catch(std::exception& e) {
    std::cerr << '\n' << "EXCEPTION OCCURED - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  DBG_PRINTLN("#== END ==#");

  return ExitCode::OK;
}
