// STL Includes:
#include <functional>
#include <iostream>

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>
#include <sstream>
#include <string>

// Includes:
#include "config/config.hpp"
#include "container/file_buffer.hpp"
#include "debug/log.hpp"
#include "interpreter/tree_walk/tree_walk.hpp"
#include "parser/awk/awk_parser.hpp"
#include "visitor/print_visitor.hpp"

// Local Includes:
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
auto parse_args(Config& t_config, CLI::App& t_app, const int t_argc,
                char* t_argv[]) -> void
{
  t_app.failure_message(CLI::FailureMessage::help);

  // Program files
  t_app
    .add_option("-f,--file", t_config.m_scripts,
                "AWX program that needs to be executed")
    ->check(CLI::ExistingFile);

  // Version flag
  std::stringstream ss;
  ss << "Version: " << AWX_VERSION;
  t_app.set_version_flag("-V,--version", ss.str(), "Displays the AWX version.");

  // Remaining positional arguments are filepaths preceding -- is optional
  t_app.add_option("{}", t_config.m_filepaths, "Postional arguments")
    ->check(CLI::ExistingFile);

  // Parse CLI args
  t_app.parse(t_argc, t_argv);
}
// NOLINTEND
auto run(Config& t_config) -> void
{
  using namespace container;

  std::vector<FileBuffer> input_vec;
  for(auto& filepath : t_config.m_filepaths) {
    input_vec.emplace_back(filepath);
  }

  // TODO: Have the program also work if no files are given (read from STDIN in
  // this case)
  if(input_vec.empty()) {
    input_vec.emplace_back();
  }

  for(auto& script : t_config.m_scripts) {
    for(auto& input : input_vec) {
      FileBuffer program{script};


      DBG_PRINTLN("=== LEXING ===");
      lexer::Lexer lexer{program};
      token::TokenStream tokenstream{lexer.tokenize()};
      DBG_PRINTLN();

      DBG_PRINTLN("=== PARSING ===");
      parser::awk::AwkParser parser{tokenstream};
      node::NodePtr ast{parser.parse()};
      DBG_PRINTLN();

#if DEBUG
      DBG_PRINTLN("=== PRETTY PRINT AST ===");
      // Pretty print AST
      visitor::PrintVisitor pretty_printer;
      ast->accept(&pretty_printer);
      DBG_PRINTLN();
#endif // DEBUG

      // Execute program via tree walk interpreter
      DBG_PRINTLN("#== EXECUTING ==#");
      interpreter::tree_walk::TreeWalk interpreter;
      interpreter.run(ast, input);
    }
  }
}

auto main(int t_argc, char* t_argv[]) -> int
{
  CLI::App app{"AWX stands for AWK With Extensions."};
  Config config{AwxMode::POSIX_AWK};

  // Parse command line arguments
  try {
    parse_args(config, app, t_argc, t_argv);
  } catch(const CLI::ParseError& e) {
    return -app.exit(e);
  }

  // Set loglevel for now for debugging purposes
  DBG_SET_LOGLEVEL(VERBOSE);
  try {
    run(config);
  } catch(std::exception& e) {
    std::cerr << '\n' << "EXCEPTION - \n" << e.what() << '\n';

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
