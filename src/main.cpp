// STL Includes:
#include <CLI/App.hpp>
#include <functional>
#include <iostream>

// Library Includes:
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>
#include <sstream>
#include <string>

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
auto parse_args(Config& t_config, CLI::App& t_app, const int t_argc,
                char* t_argv[]) -> void
{
  t_app.failure_message(CLI::FailureMessage::help);

  // Program files
  t_app
    .add_option("-f,--file", t_config.m_scripts,
                "AWX program that needs to be executed")
    ->required()
    ->check(CLI::ExistingFile);

  // Version flag
  std::stringstream ss;
  ss << "Version: " << AWX_VERSION;
  t_app.set_version_flag("-V,--version", ss.str(), "Displays the AWX version.");

  // Remaining positional arguments are filepaths preceding -- is optional
  t_app.add_option("{}", t_config.m_filepaths, "Postional arguments")
    ->required()
    ->check(CLI::ExistingFile);

  // Parse CLI args
  t_app.parse(t_argc, t_argv);
}
// NOLINTEND

auto run(Config& t_config) -> void
{
  for(auto& script : t_config.m_scripts) {
    for(auto& filepath : t_config.m_filepaths) {
      FileBuffer program{script};
      FileBuffer input{filepath};

      std::cout << "Input:\n" << input;

      lexer::Lexer lexer{program};
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
    return app.exit(e);
  }

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
