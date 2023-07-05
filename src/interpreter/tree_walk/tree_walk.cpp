#include "tree_walk.hpp"

// STL Includes:
#include <cstdio>
#include <functional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <tuple>

// Includes:
#include "../../debug/log.hpp"
#include "../../node/include.hpp"
#include "../builtin/functions.hpp"
#include "../builtin/operators.hpp"
#include "../overload.hpp"
#include "../stringify.hpp"

// Local Includes:
#include "control.hpp"


// Macros:
#define BUILTIN_CALL(t_result, t_var, t_name, ...) \
  do {                                             \
    if(t_var == #t_name) {                         \
      t_result = t_name(__VA_ARGS__);              \
    }                                              \
  } while(false)

// Using statements:
using namespace interpreter::tree_walk;

using namespace container;

using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

// Methods:
TreeWalk::TreeWalk(NodePtr t_ast, const TextBufferPtr& t_input)
  : m_ast{std::move(t_ast)}, m_nr{1}, m_resolve{true}
{
  init(t_input);
}

// Helper Methods:
//! Walk visits a node and returns its result
auto TreeWalk::walk(NodePtr t_node) -> Context&
{
  t_node->accept(this);

  return m_context;
}

auto TreeWalk::walk_list(NodeListPtr t_nodes) -> std::vector<Any>
{
  std::vector<Any> results;

  results.reserve(t_nodes->size());
  for(auto& arg : *t_nodes) {
    const auto& context{walk(arg)};

    results.push_back(context.m_result);
  }

  return results;
}


//! Evaluates the result of walking a Node and if it should be true
auto TreeWalk::eval_bool(NodePtr t_node) -> bool
{
  auto context{walk(t_node)};

  bool is_true{false};
  const auto lambda_double{[&](double t_val) {
    if(t_val) {
      is_true = true;
    }
  }};

  const auto lambda_str{[&](std::string t_val) {
    if(!t_val.empty()) {
      is_true = true;
    }
  }};

  std::visit(Overload{lambda_double, lambda_str}, context.m_result);

  return is_true;
}

auto TreeWalk::clear_context() -> void
{
  m_context.m_name.clear();
  m_context.m_result = 0.0;
}

auto TreeWalk::set(const std::string t_name, const Any t_variable) -> void
{
  m_context.m_name = t_name;

  if(!m_scope.empty() && m_scope.top().count(t_name)) {
    auto& variables{m_scope.top()};
    variables[t_name] = t_variable;
  } else {
    m_globals[t_name] = t_variable;
  }
}

auto TreeWalk::get(const std::string t_name) -> Any&
{
  m_context.m_name = t_name;

  if(!m_scope.empty() && m_scope.top().count(t_name)) {
    auto& variables{m_scope.top()};
    return variables[t_name];
  } else {
    return m_globals[t_name];
  }
}

// Visit Methods:
auto TreeWalk::visit(If* t_if) -> void
{
  if(eval_bool(t_if->condition())) {
    walk(t_if->then());
  } else {
    if(auto ptr{t_if->alt()}; ptr) {
      walk(ptr);
    }
  }
}

auto TreeWalk::visit(While* t_while) -> void
{
  while(eval_bool(t_while->condition())) {
    try {
      walk(t_while->body());
    } catch(ContinueExcept) {
    } catch(BreakExcept& e) {
      break;
    }
  }
}

auto TreeWalk::visit(DoWhile* t_do_while) -> void
{
  do {
    try {
      // eval_bool(t_do_while->body());
      walk(t_do_while->body());
    } catch(ContinueExcept) {
    } catch(BreakExcept& e) {
      break;
    }
  } while(eval_bool(t_do_while->condition()));
}

auto TreeWalk::visit(For* t_for) -> void
{
  // We just execute the init expression we do not use it
  walk(t_for->init());
  while(eval_bool(t_for->condition())) {
    try {
      walk(t_for->body());
    } catch(ContinueExcept) {
    } catch(BreakExcept& e) {
      break;
    }

    // Execute the expr at the end
    walk(t_for->expr());
  }
}

auto TreeWalk::visit(ForIn* t_for_in) -> void
{
  // TODO: Implement
}

auto TreeWalk::visit([[maybe_unused]] Continue* t_continue) -> void
{
  throw ContinueExcept{};
}

auto TreeWalk::visit([[maybe_unused]] Break* t_break) -> void
{
  throw BreakExcept{};
}

auto TreeWalk::visit([[maybe_unused]] Next* t_next) -> void
{
  throw NextExcept{};
}

auto TreeWalk::visit(Exit* t_exit) -> void
{
  if(auto ptr{t_exit->expr()}; ptr) {
    walk(ptr);
  } else {
    clear_context();
  }

  throw ExitExcept{};
}

auto TreeWalk::visit(Return* t_return) -> void
{
  if(auto ptr{t_return->expr()}; ptr) {
    walk(ptr);
  } else {
    clear_context();
  }

  // Unwind the stack
  throw ReturnExcept{};
}

auto TreeWalk::visit(Function* t_fn) -> void
{
  std::string name{t_fn->name()};

  // FIXME: For now we will completely copy the function (this is functional but
  // bad performance wise performance wise)
  m_functions[name] = std::make_shared<Function>(*t_fn);

  // A variable can be scoped by creating a constructor and destructor that sets
  // and removes the variable
}

auto TreeWalk::visit(FunctionCall* t_fn_call) -> void
{
  const std::string name{t_fn_call->name()};

  if(!m_functions.count(name)) {
    // TODO: Create separate runtime exception type
    throw std::runtime_error{"Calling to non existent function"};
  }

  auto& fn{m_functions[name]};

  // Create the stack frame
  m_scope.emplace();
  if(auto& params{*fn->params()}; !params.empty()) {
    auto iter{params.begin()};
    for(auto& arg : *t_fn_call->args()) {
      const auto& name{walk(*iter).m_name};
      const auto& result{walk(arg).m_result};

      auto& scope{m_scope.top()};
      scope[name] = result;
      iter++;
    }
  }

  try {
    walk(fn->body());

    // If the function does not return we need to clear the context
    clear_context();
  } catch(ReturnExcept& except) {
    // Call function and catch Return exception if thrown
  }

  // Pop the stack frame
  m_scope.pop();
}

auto TreeWalk::visit(BuiltinFunctionCall* t_fn) -> void
{
  using namespace builtin;

  auto name{t_fn->name()};
  auto& result{m_context.m_result};

  // Do not resolve ERE's for builtin functions
  m_resolve = false;
  auto params{walk_list(t_fn->args())};
  m_resolve = true;

  // TODO: Figure out how to clean this up
  if(params.empty()) {
    // Arithmetic functions:
    BUILTIN_CALL(result, name, rand);
    BUILTIN_CALL(result, name, srand);

    // String functions:
    BUILTIN_CALL(result, name, length, m_fields.get());
  } else if(params.size() == 1) {
    // Arithmetic functions:
    BUILTIN_CALL(result, name, cos, params[0]);
    BUILTIN_CALL(result, name, sin, params[0]);
    BUILTIN_CALL(result, name, exp, params[0]);
    BUILTIN_CALL(result, name, log, params[0]);
    BUILTIN_CALL(result, name, sqrt, params[0]);
    BUILTIN_CALL(result, name, to_int, params[0]);
    BUILTIN_CALL(result, name, srand, params[0]);

    // String functions:
    BUILTIN_CALL(result, name, length, params[0]);
    BUILTIN_CALL(result, name, tolower, params[0]);
    BUILTIN_CALL(result, name, toupper, params[0]);

    // IO and general functions:
    BUILTIN_CALL(result, name, system, params[0]);
    BUILTIN_CALL(result, name, close, params[0]);
  } else if(params.size() == 2) {
    BUILTIN_CALL(result, name, atan2, params[0], params[1]);
  }
}

auto TreeWalk::visit(SpecialPattern* t_pattern) -> void
{}

auto TreeWalk::visit(Recipe* t_recipe) -> void
{
  if(eval_bool(t_recipe->pattern())) {
    walk(t_recipe->body());
  }
}

auto TreeWalk::visit(Print* t_print) -> void
{
  // FIXME: This acts differently from when you call gawk or mawk
  if(const auto& params{t_print->params()}; params) {
    char separator = '\0';
    for(const auto& param : *params) {
      const auto& result{walk(param).m_result};

      std::visit(
        [&](auto&& t_result) {
          if(separator) {
            std::cout << separator;
          }

          std::cout << std::forward<decltype(t_result)>(t_result);
        },
        result);
      separator = ' ';

      clear_context();
    }
  }

  std::cout << '\n';
}

auto TreeWalk::visit(Printf* t_printf) -> void
{
  const auto& format{walk(t_printf->format()).m_result};
  auto& params{t_printf->params()};

  // Use std::vprintf as it takes a va_list
}

auto TreeWalk::visit(Getline* t_getline) -> void
{
  auto& [name, result] = walk(t_getline->var());

  // Get input
  std::string input;
  std::getline(std::cin, input);

  set(name, input);
}

auto TreeWalk::visit(Redirection* t_redirection) -> void
{}

auto TreeWalk::visit(Array* t_array) -> void
{
  auto& result = m_context.m_result;

  result = get(t_array->name());
}

auto TreeWalk::visit(FieldReference* t_fr) -> void
{
  auto& result{walk(t_fr->expr()).m_result};

  // Resolve field reference
  result = m_fields.get(cast(result));
}

auto TreeWalk::visit(Variable* t_var) -> void
{
  auto& result{m_context.m_result};

  result = get(t_var->name());
}

auto TreeWalk::visit(Float* t_float) -> void
{
  auto& result{m_context.m_result};

  result = t_float->get();
}

auto TreeWalk::visit(Integer* t_int) -> void
{
  auto& result{m_context.m_result};

  result = (double)t_int->get();
}

auto TreeWalk::visit(String* t_str) -> void
{
  auto& result{m_context.m_result};

  result = t_str->get();
}

auto TreeWalk::visit(Regex* t_regex) -> void
{
  auto& result{m_context.m_result};
  const auto pattern{t_regex->get()};

  // In certain contexts we do not resolve Regex expressions (Match and builtin
  // function arguments)
  if(m_resolve) {
    std::regex re{pattern, std::regex::extended};
    result = (double)std::regex_search(m_fields.get(), re);
  } else {
    result = pattern;
  }
}

// TODO: Arithmetic and Assignment visit methods could use the same function
auto TreeWalk::visit(Arithmetic* t_arithmetic) -> void
{
  using namespace builtin;

  auto lhs{walk(t_arithmetic->left())};
  auto rhs{walk(t_arithmetic->right())};
  auto& result{m_context.m_result};

  const auto lambda{[&](auto t_func) {
    result = (double)t_func(cast(lhs.m_result), cast(rhs.m_result));
  }};

  switch(const auto op{t_arithmetic->op()}; op) {
    case ArithmeticOp::POWER: {
      lambda(power<double, double>);
      break;
    }

    case ArithmeticOp::MULTIPLY: {
      lambda(multiply<double, double>);
      break;
    }

    case ArithmeticOp::DIVIDE: {
      lambda(divide<double, double>);
      break;
    }

    case ArithmeticOp::MODULO: {
      // lambda(modulo<double, double>);
      break;
    }

    case ArithmeticOp::ADD: {
      lambda(add<double, double>);
      break;
    }

    case ArithmeticOp::SUBTRACT: {
      lambda(subtract<double, double>);
      break;
    }

    default:
      // TODO: Error handling
      break;
  }
}

auto TreeWalk::visit(Assignment* t_assignment) -> void
{
  using namespace builtin;

  auto lhs{walk(t_assignment->left())};
  auto rhs{walk(t_assignment->right())};

  const auto lambda{[&](auto&& t_func) {
    set(lhs.m_name, t_func(cast(lhs.m_result), cast(rhs.m_result)));
  }};

  switch(const auto op{t_assignment->op()}; op) {
    case AssignmentOp::POWER: {
      lambda(power<double, double>);
      break;
    }

    case AssignmentOp::MULTIPLY: {
      lambda(multiply<double, double>);
      break;
    }

    case AssignmentOp::DIVIDE: {
      lambda(divide<double, double>);
      break;
    }

    case AssignmentOp::MODULO: {
      // lambda(modulo<double, double>);
      break;
    }

    case AssignmentOp::ADD: {
      lambda(add<double, double>);
      break;
    }

    case AssignmentOp::SUBTRACT: {
      lambda(subtract<double, double>);
      break;
    }

    case AssignmentOp::REGULAR: {
      set(lhs.m_name, rhs.m_result);
      break;
    }

    default:
      // TODO: Error handling
      break;
  }
}

// TODO: This method can be drastically shortened with a good lambda.
auto TreeWalk::visit(Comparison* t_comparison) -> void
{
  using namespace builtin;

  auto lhs{walk(t_comparison->left()).m_result};
  auto rhs{walk(t_comparison->right()).m_result};
  auto& result{m_context.m_result};

  switch(t_comparison->op()) {
    case ComparisonOp::LESS_THAN:
      result = (double)less_than(lhs, rhs);
      break;

    case ComparisonOp::LESS_THAN_EQUAL:
      result = (double)less_than_equal(lhs, rhs);
      break;

    case ComparisonOp::EQUAL:
      result = (double)equal(lhs, rhs);
      break;

    case ComparisonOp::NOT_EQUAL:
      result = (double)not_equal(lhs, rhs);
      break;

    case ComparisonOp::GREATER_THAN:
      result = (double)greater_than(lhs, rhs);
      break;

    case ComparisonOp::GREATER_THAN_EQUAL:
      result = (double)greater_than_equal(lhs, rhs);
      break;
  }
}

// TODO: Implement postfix increment
auto TreeWalk::visit(Increment* t_increment) -> void
{
  auto lhs{walk(t_increment->left())};
  auto& var{m_globals[lhs.m_name]};

  var = cast(var) + 1.0;
}

// TODO: Implement postfix increment
auto TreeWalk::visit(Decrement* t_decrement) -> void
{
  auto lhs{walk(t_decrement->left())};
  auto& var{m_globals[lhs.m_name]};

  var = cast(var) - 1.0;
}

auto TreeWalk::visit(Delete* t_delete) -> void
{}

auto TreeWalk::visit(Match* t_match) -> void
{
  double result{0.0};
  const auto op{t_match->op()};

  m_resolve = false;

  if(op == MatchOp::MATCH) {
    const auto& lhs{walk(t_match->left())};
    const auto& rhs{walk(t_match->right())};

    const auto string{stringify(lhs.m_result)};
    const auto pattern{stringify(rhs.m_result)};

    std::regex re{pattern, std::regex::extended};
    result = (double)std::regex_search(string, re);

    if(op != MatchOp::NO_MATCH) {
      result = result ? 0.0 : 1.0;
    }
  }

  m_resolve = true;
  m_context.m_result = result;
}

auto TreeWalk::visit(Not* t_not) -> void
{
  const auto lhs{eval_bool(t_not->left())};

  if(lhs) {
    m_context.m_result = 0.0;
  } else {
    m_context.m_result = 1.0;
  }
}

auto TreeWalk::visit(And* t_and) -> void
{
  const auto lhs{eval_bool(t_and->left())};
  const auto rhs{eval_bool(t_and->right())};

  if(lhs && rhs) {
    m_context.m_result = 1.0;
  } else {
    m_context.m_result = 0.0;
  }
}

auto TreeWalk::visit(Or* t_or) -> void
{
  const auto lhs{eval_bool(t_or->left())};
  const auto rhs{eval_bool(t_or->right())};

  if(lhs || rhs) {
    m_context.m_result = 1.0;
  } else {
    m_context.m_result = 0.0;
  }
}

auto TreeWalk::visit(StringConcatenation* t_conc) -> void
{
  const auto lhs{walk(t_conc->left())};
  const auto rhs{walk(t_conc->right())};

  std::stringstream ss;
  ss << stringify(lhs.m_result) << stringify(rhs.m_result);

  m_context.m_result = ss.str();
}

auto TreeWalk::visit(Grouping* t_grouping) -> void
{
  walk(t_grouping->left());
}

auto TreeWalk::visit(Ternary* t_ternary) -> void
{
  if(eval_bool(t_ternary->condition())) {
    walk(t_ternary->then());
  } else {
    walk(t_ternary->alt());
  }
}

auto TreeWalk::visit(UnaryPrefix* t_unary_prefix) -> void
{
  auto context{walk(t_unary_prefix->left())};
  auto& result{m_context.m_result};

  switch(t_unary_prefix->op()) {
    case UnaryPrefixOp::PLUS:
      result = +cast(result);
      break;

    case UnaryPrefixOp::MINUS:
      result = -cast(result);
      break;
  }
}

auto TreeWalk::visit(List* t_list) -> void
{
  // Evaluate every item in the list
  for(const auto& element : *t_list) {
    element->accept(this);
  }
}

auto TreeWalk::visit([[maybe_unused]] Nil* t_nil) -> void
{}

// Runtime methods:
//! Set all of the defaults
auto TreeWalk::init(const container::TextBufferPtr& t_input) -> void
{
  // TODO: Clean this up
  // set("CONVFMT", "%.6g");
  // set("OFMT", "%.6g");
  set("FILENAME", t_input->path().string());

  set("FS", " ");
  set("OFS", " ");

  set("SUBSEP", "\034");

  set("RS", "\n");
  set("ORS", "\n");

  // TODO: Implement these special variables
  // set("NF", " ");

  update(t_input);
}

auto TreeWalk::update(const container::TextBufferPtr& t_input) -> void
{
  set("NR", (double)m_nr);
  set("FNR", (double)t_input->size());
}

auto TreeWalk::run(const TextBufferPtr& t_input) -> void
{
  update(t_input);

  m_fields.set(" ", t_input->line());
  try {
    m_ast->accept(this);
  } catch(NextExcept& except) {
  } catch(ExitExcept& except) {
    // TODO: Should we exit here?
    std::exit(cast(m_context.m_result));
  }

  m_nr++;
}
