#include "tree_walk_interpreter.hpp"

// STL Includes:
#include <functional>
#include <iostream>
#include <sstream>
#include <tuple>

// Includes:
#include "../node/include.hpp"


using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

using namespace visitor;

auto TreeWalkInterpreter::visit(If* t_if) -> void
{}

auto TreeWalkInterpreter::visit(While* t_while) -> void
{}

auto TreeWalkInterpreter::visit(For* t_for) -> void
{}

auto TreeWalkInterpreter::visit(ForIn* t_for) -> void
{}

auto TreeWalkInterpreter::visit(Return* t_return) -> void
{}

auto TreeWalkInterpreter::visit(Function* t_fn) -> void
{}

auto TreeWalkInterpreter::visit(FunctionCall* t_fn_call) -> void
{}

auto TreeWalkInterpreter::visit(BuiltinFunction* t_fn) -> void
{}

auto TreeWalkInterpreter::visit(SpecialPattern* t_pattern) -> void
{}

auto TreeWalkInterpreter::visit(Recipe* t_recipe) -> void
{
  // TODO: Process pattern
  // t_recipe->pattern()->accept(this);

  t_recipe->body()->accept(this);
}

auto TreeWalkInterpreter::visit(Print* t_print) -> void
{
  if(const auto& params{t_print->params()}; params) {
    char separator;
    for(const auto& param : *params) {
      param->accept(this);
      std::visit(
        [&](auto&& t_result) {
          std::cout << separator << std::forward<decltype(t_result)>(t_result);
        },
        m_result);
      separator = ' ';
    }
  }

  std::cout << '\n';
}

auto TreeWalkInterpreter::visit(Printf* t_printf) -> void
{}

auto TreeWalkInterpreter::visit(Getline* t_getline) -> void
{}

auto TreeWalkInterpreter::visit(Redirection* t_redirection) -> void
{}

auto TreeWalkInterpreter::visit(Array* t_array) -> void
{
  // As result set the name and current value of the variable
  m_name = t_array->name();
  // m_result = m_variables[m_name];
}

auto TreeWalkInterpreter::visit(FieldReference* t_fr) -> void
{}

auto TreeWalkInterpreter::visit(Variable* t_var) -> void
{
  // As result set the name and current value of the variable
  m_name = t_var->name();
  m_result = m_variables[m_name];
}

auto TreeWalkInterpreter::visit(Float* t_float) -> void
{
  m_result = t_float->get();
}

auto TreeWalkInterpreter::visit(Integer* t_int) -> void
{
  m_result = t_int->get();
}

auto TreeWalkInterpreter::visit(String* t_str) -> void
{
  m_result = t_str->get();
}

auto TreeWalkInterpreter::visit(Regex* t_regex) -> void
{}

auto TreeWalkInterpreter::visit(Arithmetic* t_arithmetic) -> void
{
  //! Helper struct for using overloading to select correct lambda
  // template<typename... Args>
  // struct overloaded : Args... {
  //   using Args::operator()...;
  // };

  const auto lambda{[&]() -> std::tuple<Any, Any> {
    t_arithmetic->left()->accept(this);
    Any lhs{m_result};

    t_arithmetic->right()->accept(this);

    return {lhs, m_result};
  }};

  switch(const auto op{t_arithmetic->op()}; op) {
    case ArithmeticOp::POWER: {
      break;
    }

    case ArithmeticOp::MULTIPLY: {
      break;
    }
    case ArithmeticOp::DIVIDE: {
      break;
    }
    case ArithmeticOp::MODULO: {
      break;
    }
    case ArithmeticOp::ADD: {
      auto [lhs, rhs] = lambda();
      break;
    }

    case ArithmeticOp::SUBTRACT: {
      break;
    }

    default:
      // TODO: Error handling
      break;
  }
}

auto TreeWalkInterpreter::visit(Assignment* t_assignment) -> void
{
  t_assignment->left()->accept(this);
  const std::string name{m_name};

  t_assignment->right()->accept(this);
  switch(const auto op{t_assignment->op()}; op) {
    case AssignmentOp::POWER: {
      break;
    }

    case AssignmentOp::MULTIPLY: {
      break;
    }

    case AssignmentOp::DIVIDE: {
      break;
    }

    case AssignmentOp::MODULO: {
      break;
    }

    case AssignmentOp::ADD: {
      break;
    }

    case AssignmentOp::SUBTRACT: {
      break;
    }

    case AssignmentOp::REGULAR: {
      m_variables[name] = m_result;
      break;
    }

    default:
      // TODO: Error handling
      break;
  }
}

auto TreeWalkInterpreter::visit(Comparison* t_comparison) -> void
{}

auto TreeWalkInterpreter::visit(Increment* t_increment) -> void
{}

auto TreeWalkInterpreter::visit(Decrement* t_decrement) -> void
{}

auto TreeWalkInterpreter::visit(Delete* t_delete) -> void
{}

auto TreeWalkInterpreter::visit(Match* t_match) -> void
{}

auto TreeWalkInterpreter::visit(Not* t_not) -> void
{}

auto TreeWalkInterpreter::visit(And* t_and) -> void
{}

auto TreeWalkInterpreter::visit(Or* t_or) -> void
{}

auto TreeWalkInterpreter::visit(StringConcatenation* t_conc) -> void
{
  t_conc->left()->accept(this);
  Any left = m_result;

  t_conc->right()->accept(this);

  std::stringstream ss;
  std::visit(
    [&](auto&& t_left, auto&& t_right) {
      ss << t_left << t_right;
    },
    left, m_result);

  m_result = ss.str();
}

auto TreeWalkInterpreter::visit(Grouping* t_grouping) -> void
{}

auto TreeWalkInterpreter::visit(Ternary* t_ternary) -> void
{}

auto TreeWalkInterpreter::visit(UnaryPrefix* t_unary_prefix) -> void
{
  const auto visit{[&](auto&& t_lambda) {
    std::visit(
      [&](auto&& t_left) {
        using T = decltype(t_left);
        if constexpr(std::is_same<T, int>() || std::is_same<T, double>()) {
          lambda(std::forward<decltype(t_left)>());
        } else {
          m_result = 0;
        }
      },
      m_result);
  }};

  switch(t_unary_prefix->op()) {
    case UnaryPrefixOp::PLUS:
      visit([&](auto&& t_left) {
        m_result = +t_left;
      });
      break;

    case UnaryPrefixOp::MINUS:
      visit([&](auto&& t_left) {
        m_result = -t_left;
      });
      break;

    default:
      // TODO: Error handling
      break;
  }
}

auto TreeWalkInterpreter::visit(List* t_list) -> void
{
  for(const auto& element : *t_list) {
    element->accept(this);
  }
}

auto TreeWalkInterpreter::visit([[maybe_unused]] Nil* t_nil) -> void
{}
