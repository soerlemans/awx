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

// Local Includes:
#include "bool_guard.hpp"
#include "control.hpp"


// Macros:
/*! This macro assumes that a variable called name contains the name of the
 * builtin function
 */
#define BUILTIN_CALL(t_name, ...)               \
  do {                                          \
    if(t_fn_id == #t_name) {                    \
      m_context.m_result = t_name(__VA_ARGS__); \
    }                                           \
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
  : m_init{false}, m_ast{std::move(t_ast)}, m_nr{1}, m_resolve{true}
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

auto TreeWalk::walk(NodeListPtr t_nodes) -> Contexts
{
  Contexts results;

  results.reserve(t_nodes->size());
  for(auto& arg : *t_nodes) {
    const auto& context{walk(arg)};

    results.push_back(context);
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
  m_context.m_identifier.clear();
  m_context.m_result = 0.0;
}

auto TreeWalk::set(const std::string t_name, const Any t_variable) -> void
{
  m_context.m_identifier = t_name;

  if(!m_scope.empty() && m_scope.top().count(t_name)) {
    auto& variables{m_scope.top()};
    variables[t_name] = t_variable;
  } else {
    m_globals[t_name] = t_variable;
  }
}

auto TreeWalk::get(const std::string t_name) -> Any&
{
  m_context.m_identifier = t_name;

  if(!m_scope.empty() && m_scope.top().count(t_name)) {
    auto& variables{m_scope.top()};
    return variables[t_name];
  } else {
    return m_globals[t_name];
  }
}

auto TreeWalk::builtin(const std::string_view t_fn_id, Contexts& t_params)
  -> void
{
  using namespace builtin;

  const auto is_substitution{[&]() -> bool {
    return t_fn_id == "gsub" || t_fn_id == "sub";
  }};

  // TODO: Figure out how to clean this up
  if(t_params.empty()) {
    // Arithmetic functions:
    BUILTIN_CALL(rand);
    BUILTIN_CALL(srand);

    // String functions:
    BUILTIN_CALL(length, m_fields.get());
  } else if(t_params.size() == 1) {
    auto first{t_params.front().m_result};

    // Arithmetic functions:
    BUILTIN_CALL(cos, first.num());
    BUILTIN_CALL(sin, first.num());
    BUILTIN_CALL(exp, first.num());
    BUILTIN_CALL(log, first.num());
    BUILTIN_CALL(sqrt, first.num());

    // int function has different t_fn_id from to_int
    // TODO: Remove
    if(t_fn_id == "int") {
      m_context.m_result = to_int(first.num());
    }

    BUILTIN_CALL(srand, first.num());

    // String functions:
    BUILTIN_CALL(length, first.str());
    BUILTIN_CALL(tolower, first.str());
    BUILTIN_CALL(toupper, first.str());

    // IO and general functions:
    BUILTIN_CALL(system, first.str());
    BUILTIN_CALL(close, first.num());
  } else if(auto first{t_params.front().m_result}; t_params.size() == 2) {
    auto second{t_params[1].m_result};

    // Arithmetic functions:
    BUILTIN_CALL(atan2, first.num(), second.num());

    // String functions:
    // TODO: Move this somewhere more appropiate
    double rstart{0.0}, rlength{0.0};
    BUILTIN_CALL(match, first.str(), second.str(), rstart, rlength);

    set("RSTART", rstart);
    set("RLENGTH", rlength);

    BUILTIN_CALL(index, first.str(), second.str());
    BUILTIN_CALL(split, first, second, get("FS"));

    BUILTIN_CALL(substr, first.str(), second.num());

    if(is_substitution()) {
      // Field reference optional argument
      auto field{m_fields.get()};

      BUILTIN_CALL(gsub, first.str(), second.str(), field);
      BUILTIN_CALL(sub, first.str(), second.str(), field);

      m_fields.set(get("FS").str(), field);
    }
  } else if(auto second{t_params[1].m_result}; t_params.size() == 3) {
    auto third{t_params[2].m_result};

    BUILTIN_CALL(split, first, second, third);
    BUILTIN_CALL(substr, first.str(), second.num(), third.num());

    if(is_substitution()) {
      const auto var_id{t_params[2].m_identifier};
      auto target{third.str()};

      BUILTIN_CALL(gsub, first.str(), second.str(), target);
      BUILTIN_CALL(sub, first.str(), second.str(), target);

      set(var_id, target);
    }
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
  std::string identifier{t_fn->identifier()};

  // FIXME: For now we will completely copy the function (this is functional but
  // bad performance wise performance wise)
  m_functions[identifier] = std::make_shared<Function>(*t_fn);

  // A variable can be scoped by creating a constructor and destructor that sets
  // and removes the variable
}

auto TreeWalk::visit(FunctionCall* t_fn_call) -> void
{
  const std::string identifier{t_fn_call->identifier()};

  if(!m_functions.count(identifier)) {
    // TODO: Create separate runtime exception type
    throw std::runtime_error{"Calling to non existent function"};
  }

  auto& fn{m_functions[identifier]};

  // Create the stack frame
  m_scope.emplace();
  if(auto& params{*fn->params()}; !params.empty()) {
    auto iter{params.begin()};
    for(auto& arg : *t_fn_call->args()) {
      const auto& identifier{walk(*iter).m_identifier};
      const auto& result{walk(arg).m_result};

      auto& scope{m_scope.top()};
      scope[identifier] = result;
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
  const auto fn_id{t_fn->identifier()};

  // Do not resolve regex expressions for builtin functions
  m_resolve = false;
  auto params{walk(t_fn->args())};
  m_resolve = true;

  builtin(fn_id, params);
}

auto TreeWalk::visit(SpecialPattern* t_pattern) -> void
{
  if(m_init) {
    // TODO: Push Special patterns onto a BEGIN and END stack!
  }
}

auto TreeWalk::visit(Recipe* t_recipe) -> void
{
  // Evaluate the recipe
  if(eval_bool(t_recipe->condition())) {
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

  result = get(t_array->identifier());
}

auto TreeWalk::visit(FieldReference* t_fr) -> void
{
  auto& result{walk(t_fr->expr()).m_result};

  // Resolve field reference
  result = m_fields.get((std::size_t)result.num());
}

auto TreeWalk::visit(Variable* t_var) -> void
{
  auto& result{m_context.m_result};

  result = get(t_var->identifier());
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
    result = (double)t_func(lhs.m_result.num(), rhs.m_result.num());
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
    set(lhs.m_identifier, t_func(lhs.m_result.num(), rhs.m_result.num()));
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
      set(lhs.m_identifier, rhs.m_result);
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
  auto& var{m_globals[lhs.m_identifier]};

  var = var.num() + 1.0;
}

// TODO: Implement postfix increment
auto TreeWalk::visit(Decrement* t_decrement) -> void
{
  auto lhs{walk(t_decrement->left())};
  auto& var{m_globals[lhs.m_identifier]};

  var = var.num() - 1.0;
}

auto TreeWalk::visit(Delete* t_delete) -> void
{}

auto TreeWalk::visit(Match* t_match) -> void
{
  BoolGuard guard{m_resolve, false};

  const auto string{walk(t_match->left()).m_result.str()};
  const auto pattern{walk(t_match->right()).m_result.str()};

  std::regex re{pattern, std::regex::extended};
  auto found = std::regex_search(string, re);

  double result{0.0};
  switch(t_match->op()) {
    case MatchOp::MATCH:
      result = (found) ? 1.0 : 0.0;
      break;

    case MatchOp::NO_MATCH:
      result = (found) ? 0.0 : 1.0;
      break;

    default:
      // TODO: Throw
      break;
  }

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
  ss << lhs.m_result.str() << rhs.m_result.str();

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
      result = +result.num();
      break;

    case UnaryPrefixOp::MINUS:
      result = -result.num();
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
auto TreeWalk::init(const TextBufferPtr& t_input) -> void
{
  BoolGuard guard{m_init, true};

  const auto tp{t_input->position()};

  // TODO: Clean this up
  // set("CONVFMT", "%.6g");
  // set("OFMT", "%.6g");

  set("FILENAME", tp.m_source);

  set("FS", " ");
  set("OFS", " ");

  set("SUBSEP", "\034");

  set("RS", "\n");
  set("ORS", "\n");

  // TODO: Implement these special variables
  // set("NF", " ");

  update(t_input);
}

auto TreeWalk::update(const TextBufferPtr& t_input) -> void
{
  set("NR", (double)m_nr);
  set("FNR", (double)t_input->size());
}

auto TreeWalk::run(const TextBufferPtr& t_input) -> void
{
  update(t_input);

  // TODO: Create a method for this
  m_fields.set(get("FS").str(), t_input->line());

  try {
    m_ast->accept(this);
  } catch(NextExcept& except) {
  } catch(ExitExcept& except) {
    // TODO: Should we exit here?
    std::exit(m_context.m_result.num());
  }

  m_nr++;
}
