// STL Includes:
#include <functional>
#include <iostream>

// Library Includes:
#include <CLI/CLI.hpp>

// Includes:
#include "config/config.hpp"
#include "debug/log.hpp"
#include "file_buffer.hpp"
#include "interpreter/tree_walk.hpp"
#include "parser/awk_parser.hpp"
#include "visitor/print_visitor.hpp"

// Local Includes:
#include "enum.hpp"
#include "version.hpp"

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
auto parse_args(Config& t_config, const int t_argc, char* t_argv[]) -> int
{
  CLI::App app{"AWX stands for AWK With Extensions."};
  app.remaining(true); // Dont discard extra positional arguments

  std::string program_path;
  app.add_option("-f,--file", program_path,
                 "AWX program that needs to be executed");


  bool version{false};
  app.add_flag("-v,--version", version, "Display the current AWX version");

  std::vector<std::string> filenames;
  app.add_option("{}", filenames, "Postional arguments");

  CLI11_PARSE(app, t_argc, t_argv);

  t_config.m_paths.push_back(program_path);

  for(auto& i : filenames)
    std::cout << "file: " << i << '\n';

  // TODO: Improve this (temporary)
  if(version) {
    std::cout << "Version: " << t_config.m_version << '\n';
    exit(0);
  }

  return ExitCode::OK;
}
// NOLINTEND

auto run(Config& t_config) -> void
{
  // TODO: Remove this is temporary testing code
  if(t_config.m_paths.empty())
    return;

  FileBuffer fb{t_config.m_paths.front()};

  lexer::Lexer lexer{fb};
  token::TokenStream tokenstream{lexer.tokenize()};

  parser::AwkParser parser{tokenstream};
  node::NodePtr ast{parser.parse()};

#if DEBUG
  // Pretty print ast
  visitor::PrintVisitor pretty_printer;
  ast->accept(&pretty_printer);
#endif // DEBUG

  // Execute program via tree walk interpreter
  DBG_PRINTLN("#== EXECUTING ==#");
  interpreter::TreeWalk interpreter;
  ast->accept(&interpreter);
}

auto main(int t_argc, char* t_argv[]) -> int
{
  Config config{AwxMode::AWK, AWX_VERSION};

  parse_args(config, t_argc, t_argv);

  // Set loglevel for now for debugging purposes
  DBG_SET_LOGLEVEL(VERBOSE);
  DBG_PRINTLN("#== BEGIN ==#");

  try {
    run(config);
  } catch(std::exception& e) {
    std::cerr << '\n' << "EXCEPTION OCCURED - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  DBG_PRINTLN("#== END ==#");

  return ExitCode::OK;
}
