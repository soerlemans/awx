#include "tree_walk.hpp"

// STL Includes:
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <tuple>

// Includes:
#include "../../debug/log.hpp"
#include "../../node/include.hpp"
#include "../builtin/operators.hpp"
#include "../overload.hpp"

// Local Includes:
#include "control.hpp"


// Using statements:
using namespace interpreter::tree_walk;

using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

// Public Methods:
auto TreeWalk::walk(NodePtr t_node) -> Context&
{
  t_node->accept(this);

  return m_context;
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

auto TreeWalk::double2str(const double t_number) -> std::string
{
  std::stringstream ss;

  const auto precision{std::numeric_limits<decltype(t_number)>::digits10};
  ss << std::setprecision(precision) << t_number;

  return ss.str();
}

auto TreeWalk::clear_context() -> void
{
  m_context.m_name.clear();
  m_context.m_result = 0.0;
}

auto TreeWalk::set_variable(const std::string t_name, const Any t_variable)
  -> void
{
  m_context.m_name = t_name;

  if(!m_scope.empty() && m_scope.top().count(t_name)) {
    auto& variables{m_scope.top()};
    variables[t_name] = t_variable;
  } else {
    m_globals[t_name] = t_variable;
  }
}

auto TreeWalk::get_variable(const std::string t_name) -> Any&
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
    // TODO: Check for nullptr, We should probably make If::m_alt point to a Nil
    // Node
    if(auto ptr{t_if->alt()}; ptr) {
      walk(ptr);
    }
  }
}

auto TreeWalk::visit(While* t_while) -> void
{
  while(eval_bool(t_while->condition())) {
    eval_bool(t_while->body());
  }
}

auto TreeWalk::visit(For* t_for) -> void
{
  // We just execute the init expression we do not use it
  walk(t_for->init());
  while(eval_bool(t_for->condition())) {
    walk(t_for->body());

    // Execute the expr at the end
    walk(t_for->expr());
  }
}

auto TreeWalk::visit(ForIn* t_for) -> void
{}

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

auto TreeWalk::visit(node::control::Next* t_next) -> void
{
  throw NextExcept{};
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
  // TODO: Convert each of these to a case and call
  // DEFINE_RESERVED(g_atan2,    "atan2",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_close,    "close",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_cos,      "cos",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_exp,      "exp",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_gsub,     "gsub",     BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_int,      "int",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_index,    "index",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_length,   "length",   BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_log,      "log",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_match,    "match",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_rand,     "rand",     BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_sin,      "sin",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_split,    "split",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_sprintf,  "sprintf",  BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_sqrt,     "sqrt",     BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_srand,    "srand",    BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_sub,      "sub",      BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_substr,   "substr",   BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_system,   "system",   BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_tolower,  "tolower",  BUILTIN_FUNCTION);
  // DEFINE_RESERVED(g_toupper,  "toupper",  BUILTIN_FUNCTION);
}

auto TreeWalk::visit(SpecialPattern* t_pattern) -> void
{}

auto TreeWalk::visit(Recipe* t_recipe) -> void
{
  // TODO: Process pattern
  walk(t_recipe->pattern());
  // if(){

  walk(t_recipe->body());

  //}
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
  // auto format{walk(t_printf->format())};
  // std::printf();
}

auto TreeWalk::visit(Getline* t_getline) -> void
{
  auto& [name, result] = walk(t_getline->var());

  // Get input
  std::string input;
  std::cin >> input;

  set_variable(name, input);
}

auto TreeWalk::visit(Redirection* t_redirection) -> void
{}

auto TreeWalk::visit(Array* t_array) -> void
{
  auto& result = m_context.m_result;

  result = get_variable(t_array->name());
}

auto TreeWalk::visit(FieldReference* t_fr) -> void
{}

auto TreeWalk::visit(Variable* t_var) -> void
{
  auto& result = m_context.m_result;

  result = get_variable(t_var->name());
}

auto TreeWalk::visit(Float* t_float) -> void
{
  auto& result = m_context.m_result;

  result = t_float->get();
}

auto TreeWalk::visit(Integer* t_int) -> void
{
  auto& result{m_context.m_result};

  // TODO: Maybe not separate type system in float and integer?
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

  result = t_regex->get();
}

auto TreeWalk::visit(Arithmetic* t_arithmetic) -> void
{
  using namespace builtin;

  auto lhs{walk(t_arithmetic->left())};
  auto rhs{walk(t_arithmetic->right())};

  auto lambda{[&](auto t_func) {
    std::visit(Overload{[&](std::string& t_lhs, std::string& t_rhs) {
                          // One argument must be converted to a double as the
                          // convert function for binary operations will use the
                          // same operation on strings as doubles
                          m_context.m_result =
                            (double)t_func(convert(t_lhs), t_rhs);
                        },
                        [&](auto&& t_lhs, auto&& t_rhs) {
                          m_context.m_result = (double)t_func(t_lhs, t_rhs);
                        }},
               lhs.m_result, rhs.m_result);
  }};

  switch(const auto op{t_arithmetic->op()}; op) {
    case ArithmeticOp::POWER: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return power(t_lhs, t_rhs);
      });
      break;
    }

    case ArithmeticOp::MULTIPLY: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return multiply(t_lhs, t_rhs);
      });
      break;
    }

    case ArithmeticOp::DIVIDE: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return divide(t_lhs, t_rhs);
      });
      break;
    }

    case ArithmeticOp::MODULO: {
      // lambda([](auto&& t_lhs, auto&& t_rhs) {
      //   return modulo(t_lhs, t_rhs);
      // });
      break;
    }

    case ArithmeticOp::ADD: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return add(t_lhs, t_rhs);
      });
      break;
    }

    case ArithmeticOp::SUBTRACT: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return subtract(t_lhs, t_rhs);
      });
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

  auto lambda{[&](auto t_func) {
    std::visit(Overload{[&](std::string& t_lhs, std::string& t_rhs) {
                          set_variable(lhs.m_name,
                                       t_func(convert(t_lhs), t_rhs));
                        },
                        [&](auto&& t_lhs, auto&& t_rhs) {
                          set_variable(lhs.m_name, t_func(t_lhs, t_rhs));
                        }},
               lhs.m_result, rhs.m_result);
  }};

  switch(const auto op{t_assignment->op()}; op) {
    case AssignmentOp::POWER: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return power(t_lhs, t_rhs);
      });
      break;
    }

    case AssignmentOp::MULTIPLY: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return multiply(t_lhs, t_rhs);
      });
      break;
    }

    case AssignmentOp::DIVIDE: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return divide(t_lhs, t_rhs);
      });
      break;
    }

    case AssignmentOp::MODULO: {
      // lambda([](auto&& t_lhs, auto&& t_rhs) {
      //   return modulo(t_lhs, t_rhs);
      // });
      break;
    }

    case AssignmentOp::ADD: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return add(t_lhs, t_rhs);
      });
      break;
    }

    case AssignmentOp::SUBTRACT: {
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return subtract(t_lhs, t_rhs);
      });
      break;
    }

    case AssignmentOp::REGULAR: {
      set_variable(lhs.m_name, rhs.m_result);
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

  auto lhs{walk(t_comparison->left())};
  auto rhs{walk(t_comparison->right())};

  auto lambda{[&](auto t_func) {
    std::visit(
      [&](auto&& t_lhs, auto&& t_rhs) {
        m_context.m_result = (double)t_func(t_lhs, t_rhs);
      },
      lhs.m_result, rhs.m_result);
  }};

  switch(t_comparison->op()) {
    case ComparisonOp::LESS_THAN:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return less_than(t_lhs, t_rhs);
      });
      break;

    case ComparisonOp::LESS_THAN_EQUAL:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return less_than_equal(t_lhs, t_rhs);
      });
      break;

    case ComparisonOp::EQUAL:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return less_than_equal(t_lhs, t_rhs);
      });
      break;

    case ComparisonOp::NOT_EQUAL:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return not_equal(t_lhs, t_rhs);
      });
      break;

    case ComparisonOp::GREATER_THAN:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return greater_than(t_lhs, t_rhs);
      });
      break;

    case ComparisonOp::GREATER_THAN_EQUAL:
      lambda([](auto&& t_lhs, auto&& t_rhs) {
        return greater_than_equal(t_lhs, t_rhs);
      });
      break;
  }
}

// TODO: Implement postfix increment
auto TreeWalk::visit(Increment* t_increment) -> void
{
  auto lhs{walk(t_increment->left())};
  auto& var{m_globals[lhs.m_name]};

  std::visit(Overload{[&](double& t_left) {
                        t_left++;
                      },
                      [&](const std::string& t_left) {
                        var = convert(t_left) + 1.0;
                      }},
             var);
}

// TODO: Implement postfix increment
auto TreeWalk::visit(Decrement* t_decrement) -> void
{
  auto lhs{walk(t_decrement->left())};
  auto& var{m_globals[lhs.m_name]};

  std::visit(Overload{[&](double& t_left) {
                        t_left--;
                      },
                      [&](const std::string& t_left) {
                        var = convert(t_left) - 1.0;
                      }},
             var);
}

auto TreeWalk::visit(Delete* t_delete) -> void
{}

auto TreeWalk::visit(Match* t_match) -> void
{}

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
  Any left{walk(t_conc->left()).m_result};
  Any right{walk(t_conc->right()).m_result};

  std::stringstream ss;
  std::visit(
    [&](auto&& t_left, auto&& t_right) {
      ss << t_left << t_right;
    },
    left, right);

  m_context.m_result = ss.str();
}

auto TreeWalk::visit(Grouping* t_grouping) -> void
{}

auto TreeWalk::visit(Ternary* t_ternary) -> void
{}

auto TreeWalk::visit(UnaryPrefix* t_unary_prefix) -> void
{
  auto context{walk(t_unary_prefix->left())};

  switch(t_unary_prefix->op()) {
    case UnaryPrefixOp::PLUS:
      std::visit(Overload{[&](double t_left) {
                            m_context.m_result = +t_left;
                          },
                          [](std::string& t_left) {
                          }},
                 context.m_result);
      break;

    case UnaryPrefixOp::MINUS:
      std::visit(Overload{[&](double t_left) {
                            m_context.m_result = -t_left;
                          },
                          [](std::string& t_left) {
                          }},
                 context.m_result);
      break;
  }
}

auto TreeWalk::visit(List* t_list) -> void
{
  for(const auto& element : *t_list) {
    element->accept(this);
  }
}

auto TreeWalk::visit([[maybe_unused]] Nil* t_nil) -> void
{}

auto TreeWalk::run(NodePtr& t_ast, const FileBuffer& t_input) -> void
{
  m_input = &t_input;
  m_ast = t_ast;

  // TODO: Clean this up
  set_variable("FNR", (double)m_input->size());
  // set_variable("CONVFMT", "%.6g");
  // set_variable("OFMT", "%.6g");
  set_variable("FILENAME", m_input->path().string());

  set_variable("FS", " ");
  set_variable("OFS", " ");

  set_variable("SUBSEP", "\034");

  set_variable("$0", "\034");

  set_variable("RS", "\n");
  set_variable("ORS", "\n");

  // TODO: Implement these special variables
  // set_variable("NF", " ");

  for(std::size_t nr{1}; !m_input->eof(); m_input->next()) {
    set_variable("NR", (double)nr);
    try {
      m_ast->accept(this);
    } catch(NextExcept& except) {
    }

    nr++;
  }
}
