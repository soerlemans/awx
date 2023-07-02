// STL Includes:
#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

// Library Includes:
#include <CLI/App.hpp>
#include <CLI/CLI.hpp>
#include <CLI/Validators.hpp>

// Includes:
#include "config/config.hpp"
#include "container/file_buffer.hpp"
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "interpreter/tree_walk/tree_walk.hpp"
#include "parser/awk/awk_parser.hpp"
#include "visitor/print_visitor.hpp"

// Local Includes:
#include "benchmark.hpp"
#include "version.hpp"


// Using statements:
using namespace container;
using namespace node;

// Aliases:
using TextVec = std::vector<TextBufferPtr>;
using PolicyFunc = std::function<void(NodePtr&)>;

// Enums:
enum ExitCode {
  OK = 0,
  SIGNAL,
  EXCEPTION,
};

// Functions:
// NOLINTBEGIN
/*! Parse command line arguments and store them in a configuration class
 */
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
  t_app.add_option("{}", t_config.m_args, "Postional arguments");
  // ->check(CLI::ExistingFile);

  // Parse CLI args
  t_app.parse(t_argc, t_argv);
}
// NOLINTEND

auto init_scripts(Config& t_config) -> TextVec
{
  auto& args{t_config.m_args};
  TextVec scripts;

  // If no scrips were passed with -f use the first positional argument
  if(!t_config.m_scripts.empty()) {
    for(auto& script : t_config.m_scripts) {
      auto buffer{std::make_shared<FileBuffer>(script)};
      scripts.push_back(std::move(buffer));
    }
  } else {
    if(!args.empty()) {
      auto script{std::make_shared<TextBuffer>()};

      script->add_line(args.front());
      scripts.push_back(std::move(script));

      args.pop_front();
    } else {
      // TODO: Print manual
    }
  }

  return scripts;
}

auto init_sources(Config& t_config) -> TextVec
{
  auto& args{t_config.m_args};
  TextVec sources;

  for(auto& filepath : args) {
    sources.push_back(std::make_shared<FileBuffer>(filepath));
  }

  return sources;
}

auto source_policy(TextVec& t_sources) -> PolicyFunc
{
  using namespace interpreter::tree_walk;

  PolicyFunc policy;
  if(t_sources.empty()) {
    policy = [&](NodePtr& t_ast) {
      auto source{std::make_shared<TextBuffer>()};
      TreeWalk interpreter{t_ast, source};

      while(true) {
        std::string line;
        std::getline(std::cin, line);

        if(std::cin.eof()) {
          break;
        }

        source->add_line(line);

        interpreter.run(source);
        source->next();
      }
    };
  } else {
    policy = [&](NodePtr& t_ast) {
      for(auto& source : t_sources) {
        TreeWalk interpreter{t_ast, source};

        for(; !source->eof(); source->next()) {
          interpreter.run(source);
        }
      }
    };
  }

  return policy;
}

auto lex(TextBufferPtr t_program) -> token::TokenStream
{
  using namespace lexer;
  using namespace token;

  DBG_PRINTLN("=== LEXING ===");

  Lexer lexer{t_program};
  TokenStream tokenstream{lexer.tokenize()};

  DBG_PRINTLN();

  return tokenstream;
}

auto parse(const token::TokenStream& t_ts) -> node::NodePtr
{
  using namespace parser::awk;
  using namespace node;
  using namespace visitor;

  DBG_PRINTLN("=== PARSING ===");

  AwkParser parser{t_ts};
  NodePtr ast{parser.parse()};

#if DEBUG
  DBG_PRINTLN();
  DBG_PRINTLN("=== PRETTY PRINT AST ===");

  // Pretty print AST
  PrintVisitor pretty_printer;
  ast->accept(&pretty_printer);

#endif // DEBUG

  DBG_PRINTLN();

  return ast;
}

auto execute(const PolicyFunc t_lambda, NodePtr& t_ast) -> void
{
  using namespace interpreter::tree_walk;

  // Execute program via tree walk interpreter
  DBG_PRINTLN("#== EXECUTING ==#");

  t_lambda(t_ast);

  DBG_PRINTLN("#== END ==#");
}

// FIXME: Benchmarking this way looks ugly
auto run(Config& t_config) -> void
{
  using namespace std::chrono;

  const auto count{[](auto&& start, auto&& end) -> int {
    return duration_cast<nanoseconds>(end - start).count();
  }};

  auto start{steady_clock::now()};

  auto scripts{init_scripts(t_config)};
  auto sources{init_sources(t_config)};
  PolicyFunc policy{source_policy(sources)};
  auto startup{steady_clock::now()};

  for(auto& script : scripts) {
    auto tokenstream{lex(script)};
    auto lexing{steady_clock::now()};

    auto ast{parse(tokenstream)};
    auto parsing{steady_clock::now()};

    execute(policy, ast);
    auto execution{steady_clock::now()};

    // Display results of execution
    benchmark(TimingPair{"Startup", count(start, startup)},
              TimingPair{"Lexing", count(startup, lexing)},
              TimingPair{"Parsing", count(lexing, parsing)},
              TimingPair{"Execution", count(parsing, execution)},
              TimingPair{"=========", 0}, // FIXME: Remove separator in due time
              TimingPair{"Runtime", count(startup, execution)},
              TimingPair{"Total", count(start, execution)});
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
