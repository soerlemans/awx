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
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "interpreter/tree_walk/tree_walk.hpp"
#include "parser/awk/awk_parser.hpp"
#include "visitor/print_visitor.hpp"

// Local Includes:
#include "version.hpp"


// Using statements:
using namespace container;

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

auto lex(TextBufferPtr t_program) -> token::TokenStream
{
  DBG_PRINTLN("=== LEXING ===");

  lexer::Lexer lexer{t_program};
  token::TokenStream tokenstream{lexer.tokenize()};

  DBG_PRINTLN();

	return tokenstream;
}

auto parse(const token::TokenStream& t_ts) -> node::NodePtr
{
  DBG_PRINTLN("=== PARSING ===");

  parser::awk::AwkParser parser{t_ts};
  node::NodePtr ast{parser.parse()};

#if DEBUG
  DBG_PRINTLN();
  DBG_PRINTLN("=== PRETTY PRINT AST ===");

  // Pretty print AST
  visitor::PrintVisitor pretty_printer;
  ast->accept(&pretty_printer);

#endif // DEBUG

  DBG_PRINTLN();

  return ast;
}

auto execute(node::NodePtr& t_ast, const TextBufferPtr t_input) -> void
{
  // Execute program via tree walk interpreter
  DBG_PRINTLN("#== EXECUTING ==#");

  interpreter::tree_walk::TreeWalk interpreter;
  interpreter.run(t_ast, t_input);

  DBG_PRINTLN("#== END ==#");
}

auto run(Config& t_config) -> void
{
  std::vector<TextBufferPtr> input_vec;
  for(auto& filepath : t_config.m_filepaths) {
    input_vec.push_back(std::make_shared<FileBuffer>(filepath));
  }

  // TODO: Have the program also work if no files are given (read from STDIN in
  // this case)
  if(input_vec.empty()) {
    TextBufferPtr buffer{std::make_shared<TextBuffer>()};
    buffer->add_line("");
    input_vec.push_back(std::move(buffer));
  }

  for(auto& script : t_config.m_scripts) {
    for(auto& input : input_vec) {
      FileBufferPtr program{std::make_shared<FileBuffer>(script)};

			auto tokenstream{lex(program)};
      auto ast{parse(tokenstream)};

      execute(ast, input);
    }
  }
}

auto main(int t_argc, char* t_argv[]) -> int
{
  CLI::App app{"AWX (AWK With Extensions)"};
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
