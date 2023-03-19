#include "tree_walk_interpreter.hpp"

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
{}

auto TreeWalkInterpreter::visit(Print* t_print) -> void
{}

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
{}

auto TreeWalkInterpreter::visit(Float* t_float) -> void
{}

auto TreeWalkInterpreter::visit(Integer* t_int) -> void
{}

auto TreeWalkInterpreter::visit(String* t_str) -> void
{}

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
{}

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
{}

auto TreeWalkInterpreter::visit(Nil* t_nil) -> void
{}
