#include "tree_walk_interpreter.hpp"

// STL Includes:
#include <iostream>

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
    std::size_t index{0};
    for(const auto& param : *params) {
      param->accept(this);
      std::visit(
        [&](auto&& t_result) {
          std::cout << std::forward<decltype(t_result)>(t_result);

          // Insert spaces in between printing
          if(index < params->size() - 1)
            std::cout << ' ';
        },
        m_result);

      index++;
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
{}

auto TreeWalkInterpreter::visit(FieldReference* t_fr) -> void
{}

auto TreeWalkInterpreter::visit(Variable* t_var) -> void
{
  m_result = t_var->name();
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
  std::string name{std::get<std::string>(m_result)};

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
      m_variable_store[name] = m_result;
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
{}

auto TreeWalkInterpreter::visit(Grouping* t_grouping) -> void
{}

auto TreeWalkInterpreter::visit(Ternary* t_ternary) -> void
{}

auto TreeWalkInterpreter::visit(UnaryPrefix* t_unary_prefix) -> void
{}

auto TreeWalkInterpreter::visit(List* t_list) -> void
{
  for(const auto& element : *t_list) {
    element->accept(this);
  }
}

auto TreeWalkInterpreter::visit([[maybe_unused]] Nil* t_nil) -> void
{}
