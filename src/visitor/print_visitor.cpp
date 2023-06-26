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
{}

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

  PPRINT("FOR IN");
}

auto PrintVisitor::visit(Continue* t_continue) -> void
{
  PPRINT_INIT();

  PPRINT("Continue");
}

auto PrintVisitor::visit(Break* t_break) -> void
{
  PPRINT_INIT();

  PPRINT("Break");
}

auto PrintVisitor::visit(Next* t_next) -> void
{
  PPRINT_INIT();

  PPRINT("NEXT");
}

auto PrintVisitor::visit(Exit* t_exit) -> void
{
  PPRINT_INIT();

  PPRINT("EXIT");
}

auto PrintVisitor::visit(Return* t_return) -> void
{
  PPRINT_INIT();

  PPRINT("RETURN");
}

auto PrintVisitor::visit(Function* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("FUNCTION");
  PPRINT("| NAME: ");

  // TODO: Macro or lambda this??
  if(auto& params{t_fn->params()}; params) {
    PPRINT("| PARAMS");
    params->accept(this);
  }

  if(auto& body{t_fn->body()}; body) {
    PPRINT("| BODY");
    body->accept(this);
  }
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  PPRINT_INIT();

  PPRINT("FUNCTION CALL");
  PPRINT("| NAME: ");

  if(NodeListPtr & args{t_fn_call->args()}; args) {
    PPRINT("| ARGS");
    args->accept(this);
  }
}

auto PrintVisitor::visit(BuiltinFunctionCall* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("BUILTIN FUNCTION CALL");
}

auto PrintVisitor::visit(SpecialPattern* t_pattern) -> void
{
  PPRINT_INIT();

  PPRINT("SPECIAL PATTERN");

  // TODO: List select special pattern
}

auto PrintVisitor::visit(Recipe* t_recipe) -> void
{
  PPRINT_INIT();

  PPRINT("RECIPE");
  // TODO: Macro or lambda this??
  if(NodePtr & pattern{t_recipe->pattern()}; pattern) {
    PPRINT("| PATTERN");
    pattern->accept(this);
  }

  if(NodePtr & body{t_recipe->body()}; body) {
    PPRINT("| BODY");
    body->accept(this);
  }
}

auto PrintVisitor::visit(Print* t_print) -> void
{
  PPRINT_INIT();

  PPRINT("PRINT");
  PPRINT("| PARAMS:");

  visit(t_print->params().get());
}

auto PrintVisitor::visit(Printf* t_printf) -> void
{
  PPRINT_INIT();

  PPRINT("PRINTF");

  PPRINT("| FORMAT:");
  PPRINT("| PARAMS:");
}

auto PrintVisitor::visit(Getline* t_getline) -> void
{
  PPRINT_INIT();

  PPRINT("GETLINE");
  if(NodePtr & var{t_getline->var()}; var) {
    PPRINT("| VAR");
    var->accept(this);
  }
}

auto PrintVisitor::visit(Redirection* t_redirection) -> void
{
  PPRINT_INIT();

  PPRINT("REDIRECTION");
}

auto PrintVisitor::visit(Array* t_array) -> void
{
  PPRINT_INIT();

  PPRINT("ARRAY");
}

auto PrintVisitor::visit(FieldReference* t_fr) -> void
{
  PPRINT_INIT();

  PPRINT("FIELD REFERENCE");
  PPRINT("| EXPR");

  t_fr->expr()->accept(this);
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  PPRINT_INIT();

  PPRINT("VARIABLE");
  PPRINT("| NAME: ");
}

auto PrintVisitor::visit(Float* t_float) -> void
{
  PPRINT_INIT();

  PPRINT("FLOAT: ");
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  PPRINT_INIT();

  PPRINT("INTEGER: ");
}

auto PrintVisitor::visit(String* t_str) -> void
{
  PPRINT_INIT();

  PPRINT("STRING: ");
}

auto PrintVisitor::visit(Regex* t_regex) -> void
{
  PPRINT_INIT();

  PPRINT("REGEX: ");
}

auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  PPRINT_INIT();

  PPRINT("ARITHMETIC");
  PPRINT("| OP: TODO!");

  PPRINT("| LEFT");
  PPRINT("| RIGHT");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  PPRINT_INIT();

  PPRINT("ASSIGNMENT");
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  PPRINT_INIT();

  PPRINT("COMPARISON");

  // TODO: Add print statement for comparison operator

  PPRINT("| LEFT");
  t_comparison->left()->accept(this);

  PPRINT("| RIGHT");
  t_comparison->right()->accept(this);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  PPRINT_INIT();

  PPRINT("INCREMENT");
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  PPRINT_INIT();

  PPRINT("DECREMENT");
}

auto PrintVisitor::visit(Delete* t_delete) -> void
{
  PPRINT_INIT();

  PPRINT("DELETE");
}

auto PrintVisitor::visit(Match* t_match) -> void
{
  PPRINT_INIT();

  PPRINT("MATCH");

  PPRINT_IF("STRING", t_match->left());
  PPRINT_IF("PATTERN", t_match->right());
}

auto PrintVisitor::visit(Not* t_not) -> void
{
  PPRINT_INIT();

  PPRINT("NOT");
  PPRINT("| LEFT");
  t_not->left()->accept(this);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  PPRINT_INIT();

  PPRINT("AND");
  PPRINT("| LEFT");
  t_and->left()->accept(this);

  PPRINT("| RIGHT");
  t_and->right()->accept(this);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  PPRINT_INIT();

  PPRINT("OR");

  PPRINT("| LEFT");
  t_or->left()->accept(this);

  PPRINT("| right");
  t_or->right()->accept(this);
}

auto PrintVisitor::visit(StringConcatenation* t_conc) -> void
{
  PPRINT_INIT();

  PPRINT("STRING CONCATENATION");

  PPRINT("| LEFT");
  t_conc->left()->accept(this);

  PPRINT("| RIGHT");
  t_conc->right()->accept(this);
}

auto PrintVisitor::visit(Grouping* t_grouping) -> void
{
  PPRINT_INIT();

  PPRINT("GROUPING");
  if(auto& expr{t_grouping->left()}; expr) {
    PPRINT("| EXPR");
    expr->accept(this);
  }
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  PPRINT_INIT();

  PPRINT("TERNARY");

  if(NodePtr & condition{t_ternary->condition()}; condition) {
    PPRINT("| CONDITION");
    condition->accept(this);
  }

  if(NodePtr & then{t_ternary->then()}; then) {
    PPRINT("| THEN");
    then->accept(this);
  }

  if(NodePtr & alt{t_ternary->alt()}; alt) {
    PPRINT("| ELSE");
    alt->accept(this);
  }
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  PPRINT_INIT();

  PPRINT("UNARY PREFIX");
  PPRINT("| OP: ");

  // TODO: Implement plus or minus printing

  // Visit the unary expression
  t_unary_prefix->left()->accept(this);
}

auto PrintVisitor::visit(List* t_list) -> void
{
  PPRINT_INIT();

  PPRINT("LIST");

  for(NodePtr& node : *t_list)
    node->accept(this);
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  PPRINT_INIT();

  PPRINT("NIL");
}
