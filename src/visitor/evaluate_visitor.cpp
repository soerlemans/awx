#include "evaluate_visitor.hpp"


using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

auto EvaluateVisitor::visit(If* t_if) -> void
{}

auto EvaluateVisitor::visit(While* t_while) -> void
{}

auto EvaluateVisitor::visit(For* t_for) -> void
{}

auto EvaluateVisitor::visit(ForIn* t_for) -> void
{}

auto EvaluateVisitor::visit(Return* t_return) -> void
{}

auto EvaluateVisitor::visit(Function* t_fn) -> void
{}

auto EvaluateVisitor::visit(FunctionCall* t_fn_call) -> void
{}

auto EvaluateVisitor::visit(BuiltinFunction* t_fn) -> void
{}

auto EvaluateVisitor::visit(SpecialPattern* t_pattern) -> void
{}

auto EvaluateVisitor::visit(Recipe* t_recipe) -> void
{}

auto EvaluateVisitor::visit(Print* t_print) -> void
{}

auto EvaluateVisitor::visit(Printf* t_printf) -> void
{}

auto EvaluateVisitor::visit(Getline* t_getline) -> void
{}

auto EvaluateVisitor::visit(Redirection* t_redirection) -> void
{}

auto EvaluateVisitor::visit(Array* t_array) -> void
{}

auto EvaluateVisitor::visit(FieldReference* t_fr) -> void
{}

auto EvaluateVisitor::visit(Variable* t_var) -> void
{}

auto EvaluateVisitor::visit(Float* t_float) -> void
{}

auto EvaluateVisitor::visit(Integer* t_int) -> void
{}

auto EvaluateVisitor::visit(String* t_str) -> void
{}

auto EvaluateVisitor::visit(Regex* t_regex) -> void
{}

auto EvaluateVisitor::visit(Arithmetic* t_arithmetic) -> void
{}

auto EvaluateVisitor::visit(Assignment* t_assignment) -> void
{}

auto EvaluateVisitor::visit(Comparison* t_comparison) -> void
{}

auto EvaluateVisitor::visit(Increment* t_increment) -> void
{}

auto EvaluateVisitor::visit(Decrement* t_decrement) -> void
{}

auto EvaluateVisitor::visit(Delete* t_delete) -> void
{}

auto EvaluateVisitor::visit(Match* t_match) -> void
{}

auto EvaluateVisitor::visit(Not* t_not) -> void
{}

auto EvaluateVisitor::visit(And* t_and) -> void
{}

auto EvaluateVisitor::visit(Or* t_or) -> void
{}

auto EvaluateVisitor::visit(StringConcatenation* t_conc) -> void
{}

auto EvaluateVisitor::visit(Grouping* t_grouping) -> void
{}

auto EvaluateVisitor::visit(Ternary* t_ternary) -> void
{}

auto EvaluateVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{}

auto EvaluateVisitor::visit(List* t_list) -> void
{}

auto EvaluateVisitor::visit(Nil* t_nil) -> void
{}
