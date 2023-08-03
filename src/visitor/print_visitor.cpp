#include "print_visitor.hpp"


// Macros:
#define PPRINT_INIT() \
  Printer printer     \
  {                   \
    m_counter         \
  }

#define PPRINT(...) printer.print(__VA_ARGS__)

//! Pretty print if a member is not a nullptr
#define PPRINT_IF(t_str, t_ptr) printer.print_if(t_ptr, this, "| " t_str)

#define PPRINT_UNOP(t_str, t_ptr) \
  PPRINT(t_str);                  \
  PPRINT_IF("Left", t_ptr->left());

#define PPRINT_BINOP(t_str, t_ptr)  \
  PPRINT(t_str);                    \
  PPRINT_IF("Left", t_ptr->left()); \
  PPRINT_IF("Right", t_ptr->right());

// Using statements:
using namespace visitor;
using namespace node;
using namespace node::control;
using namespace node::functions;
using namespace node::io;
using namespace node::lvalue;
using namespace node::operators;
using namespace node::recipes;
using namespace node::rvalue;

auto PrintVisitor::visit(If* t_if) -> void
{
  PPRINT_INIT();

  PPRINT("If");
  PPRINT_IF("Then", t_if->then());
  PPRINT_IF("Alt", t_if->alt());
}

auto PrintVisitor::visit(While* t_while) -> void
{
  PPRINT_INIT();

  PPRINT("While");
  PPRINT_IF("Condition", t_while->condition());
  PPRINT_IF("Body", t_while->body());
}

auto PrintVisitor::visit(DoWhile* t_do_while) -> void
{
  PPRINT_INIT();

  PPRINT("Do While");
  PPRINT_IF("Condition", t_do_while->condition());
  PPRINT_IF("Body", t_do_while->body());
}

auto PrintVisitor::visit(For* t_for) -> void
{
  PPRINT_INIT();

  PPRINT("For");
  PPRINT_IF("Init", t_for->init());
  PPRINT_IF("Condition", t_for->condition());
  PPRINT_IF("Expr", t_for->expr());
  PPRINT_IF("Body", t_for->body());
}

auto PrintVisitor::visit(ForIn* t_for_in) -> void
{
  PPRINT_INIT();

  PPRINT("For in");
  PPRINT_IF("Identifier", t_for_in->identifier());
  PPRINT_IF("Array", t_for_in->array());
  PPRINT_IF("Body", t_for_in->body());
}

auto PrintVisitor::visit([[maybe_unused]] Continue* t_continue) -> void
{
  PPRINT_INIT();

  PPRINT("Continue");
}

auto PrintVisitor::visit([[maybe_unused]] Break* t_break) -> void
{
  PPRINT_INIT();

  PPRINT("Break");
}

auto PrintVisitor::visit([[maybe_unused]] Next* t_next) -> void
{
  PPRINT_INIT();

  PPRINT("Next");
}

auto PrintVisitor::visit(Exit* t_exit) -> void
{
  PPRINT_INIT();

  PPRINT("Exit");
  PPRINT_IF("Expr: ", t_exit->expr());
}

auto PrintVisitor::visit([[maybe_unused]] Return* t_return) -> void
{
  PPRINT_INIT();

  PPRINT("Return");
}

auto PrintVisitor::visit(Function* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("FUNCTION");
  PPRINT("| Name", t_fn->identifier());
  PPRINT_IF("Params", t_fn->params());
  PPRINT_IF("Body", t_fn->body());
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  PPRINT_INIT();

  PPRINT("Function call");
  PPRINT("| Name: ", t_fn_call->identifier());
  PPRINT_IF("Params: ", t_fn_call->args());
}

auto PrintVisitor::visit(BuiltinFunctionCall* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("Builtin function call");
  PPRINT("| Name: ", t_fn->identifier());
  PPRINT_IF("Params: ", t_fn->args());
}

auto PrintVisitor::visit(SpecialPattern* t_pattern) -> void
{
  PPRINT_INIT();

  PPRINT("Special pattern");
  // TODO: List select special pattern
}

auto PrintVisitor::visit(Recipe* t_recipe) -> void
{
  PPRINT_INIT();

  PPRINT("Recipe");
  PPRINT_IF("Pattern", t_recipe->pattern());
  PPRINT_IF("Body", t_recipe->body());
}

auto PrintVisitor::visit(Print* t_print) -> void
{
  PPRINT_INIT();

  PPRINT("Print");
  PPRINT_IF("Params:", t_print->params());
}

auto PrintVisitor::visit(Printf* t_printf) -> void
{
  PPRINT_INIT();

  PPRINT("Printf");
  // PPRINT_IF("Format:", t_printf->params());
  PPRINT_IF("Params:", t_printf->params());
}

auto PrintVisitor::visit(Getline* t_getline) -> void
{
  PPRINT_INIT();

  PPRINT("Getline");
  PPRINT_IF("Var:", t_getline->var());
}

auto PrintVisitor::visit(Redirection* t_redirection) -> void
{
  PPRINT_INIT();

  PPRINT("Redirection");
}

auto PrintVisitor::visit(Array* t_array) -> void
{
  PPRINT_INIT();

  PPRINT("Array", t_array->identifier());
}

auto PrintVisitor::visit(FieldReference* t_fr) -> void
{
  PPRINT_INIT();

  PPRINT("Field reference");
  PPRINT_IF("Expr", t_fr->expr());
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  PPRINT_INIT();

  PPRINT("Variable", t_var->identifier());
}

auto PrintVisitor::visit(Float* t_float) -> void
{
  PPRINT_INIT();

  PPRINT("Float: ", t_float->get());
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  PPRINT_INIT();

  PPRINT("Integer: ", t_int->get());
}

auto PrintVisitor::visit(String* t_str) -> void
{
  PPRINT_INIT();

  PPRINT("String: ", t_str->get());
}

auto PrintVisitor::visit(Regex* t_regex) -> void
{
  PPRINT_INIT();

  PPRINT("Regex: ", t_regex->get());
}

auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("ARITHMETIC", t_arithmetic)
  PPRINT("| OP: TODO!");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Assignment", t_assignment);
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Comparison", t_comparison);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  PPRINT_INIT();

  PPRINT("Increment");
  PPRINT("| Prefix: ", t_increment->prefix());
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  PPRINT_INIT();

  PPRINT("Decrement");
  PPRINT("| Prefix: ", t_decrement->prefix());
}

auto PrintVisitor::visit(Delete* t_delete) -> void
{
  PPRINT_INIT();

  PPRINT("Delete");
}

auto PrintVisitor::visit(Match* t_match) -> void
{
  PPRINT_INIT();

  PPRINT("Match");
  PPRINT_IF("String", t_match->left());
  PPRINT_IF("Pattern", t_match->right());
}

auto PrintVisitor::visit(Not* t_not) -> void
{
  PPRINT_INIT();

  PPRINT_UNOP("Not", t_not);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("And", t_and);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Or", t_or);
}

auto PrintVisitor::visit(StringConcatenation* t_conc) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("StringConcatenation", t_conc);
}

auto PrintVisitor::visit(Grouping* t_grouping) -> void
{
  PPRINT_INIT();

  PPRINT_UNOP("Grouping", t_grouping)
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  PPRINT_INIT();

  PPRINT("Ternary");
  PPRINT_IF("Condition", t_ternary->condition());
  PPRINT_IF("Then", t_ternary->then());
  PPRINT_IF("Alt", t_ternary->alt());
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  PPRINT_INIT();

  PPRINT("Unary prefix");
  PPRINT_UNOP("Unary prefix", t_unary_prefix)
  PPRINT("| OP: TODO");
}

auto PrintVisitor::visit(List* t_list) -> void
{
  PPRINT_INIT();

  PPRINT("List");
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  PPRINT_INIT();

  PPRINT("NIL");
}
