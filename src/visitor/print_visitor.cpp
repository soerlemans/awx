#include "print_visitor.hpp"


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
  Printer printer{m_counter};

  printer.print("If");

  printer.print_if(t_if->then(), this, "| THEN");
}

auto PrintVisitor::visit(While* t_while) -> void
{
  Printer printer{m_counter};

  printer.print("While");
  printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(DoWhile* t_do_while) -> void
{}

auto PrintVisitor::visit(For* t_for) -> void
{
  Printer printer{m_counter};

  printer.print("For");
  // printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(ForIn* t_for_in) -> void
{
  Printer printer{m_counter};

  printer.print("FOR IN");
}

auto PrintVisitor::visit(Continue* t_continue) -> void
{
  Printer printer{m_counter};

  printer.print("CONTINUE");
}

auto PrintVisitor::visit(Break* t_break) -> void
{
  Printer printer{m_counter};

  printer.print("BREAK");
}

auto PrintVisitor::visit(Next* t_next) -> void
{
  Printer printer{m_counter};

  printer.print("NEXT");
}

auto PrintVisitor::visit(Exit* t_exit) -> void
{
  Printer printer{m_counter};

  printer.print("EXIT");
}

auto PrintVisitor::visit(Return* t_return) -> void
{
  Printer printer{m_counter};

  printer.print("RETURN");
}

auto PrintVisitor::visit(Function* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION");
  printer.print("| NAME: ", t_fn->name());

  // TODO: Macro or lambda this??
  if(auto& params{t_fn->params()}; params) {
    printer.print("| PARAMS");
    params->accept(this);
  }

  if(auto& body{t_fn->body()}; body) {
    printer.print("| BODY");
    body->accept(this);
  }
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION CALL");
  printer.print("| NAME: ", t_fn_call->name());

  if(NodeListPtr & args{t_fn_call->args()}; args) {
    printer.print("| ARGS");
    args->accept(this);
  }
}

auto PrintVisitor::visit(BuiltinFunctionCall* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("BUILTIN FUNCTION CALL");
}

auto PrintVisitor::visit(SpecialPattern* t_pattern) -> void
{
  Printer printer{m_counter};

  printer.print("SPECIAL PATTERN");

  // TODO: List select special pattern
}

auto PrintVisitor::visit(Recipe* t_recipe) -> void
{
  Printer printer{m_counter};

  printer.print("RECIPE");
  // TODO: Macro or lambda this??
  if(NodePtr & pattern{t_recipe->pattern()}; pattern) {
    printer.print("| PATTERN");
    pattern->accept(this);
  }

  if(NodePtr & body{t_recipe->body()}; body) {
    printer.print("| BODY");
    body->accept(this);
  }
}

auto PrintVisitor::visit(Print* t_print) -> void
{
  Printer printer{m_counter};

  printer.print("PRINT");
  printer.print("| PARAMS:");

  visit(t_print->params().get());
}

auto PrintVisitor::visit(Printf* t_printf) -> void
{
  Printer printer{m_counter};

  printer.print("PRINTF");

  printer.print_if(t_printf->format(), this, "| FORMAT:");
  printer.print_if(t_printf->format(), this, "| PARAMS:");
}

auto PrintVisitor::visit(Getline* t_getline) -> void
{
  Printer printer{m_counter};

  printer.print("GETLINE");
  if(NodePtr & var{t_getline->var()}; var) {
    printer.print("| VAR");
    var->accept(this);
  }
}

auto PrintVisitor::visit(Redirection* t_redirection) -> void
{
  Printer printer{m_counter};

  printer.print("REDIRECTION");
}

auto PrintVisitor::visit(Array* t_array) -> void
{
  Printer printer{m_counter};

  printer.print("ARRAY");
}

auto PrintVisitor::visit(FieldReference* t_fr) -> void
{
  Printer printer{m_counter};

  printer.print("FIELD REFERENCE");
  printer.print("| EXPR");

  t_fr->expr()->accept(this);
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  Printer printer{m_counter};

  printer.print("VARIABLE");
  printer.print("| NAME: ", t_var->name());
}

auto PrintVisitor::visit(Float* t_float) -> void
{
  Printer printer{m_counter};

  printer.print("FLOAT: ", t_float->get());
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  Printer printer{m_counter};

  printer.print("INTEGER: ", t_int->get());
}

auto PrintVisitor::visit(String* t_str) -> void
{
  Printer printer{m_counter};

  printer.print("STRING: ", t_str->get());
}

auto PrintVisitor::visit(Regex* t_regex) -> void
{
  Printer printer{m_counter};

  printer.print("REGEX: ", t_regex->get());
}

auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  Printer printer{m_counter};

  printer.print("ARITHMETIC");
  printer.print("| OP: TODO!");

  printer.print_if(t_arithmetic->left(), this, "| LEFT");
  printer.print_if(t_arithmetic->right(), this, "| RIGHT");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  Printer printer{m_counter};

  printer.print("ASSIGNMENT");
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  Printer printer{m_counter};

  printer.print("COMPARISON");

  // TODO: Add print statement for comparison operator

  printer.print("| LEFT");
  t_comparison->left()->accept(this);

  printer.print("| RIGHT");
  t_comparison->right()->accept(this);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  Printer printer{m_counter};

  printer.print("INCREMENT");
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  Printer printer{m_counter};

  printer.print("DECREMENT");
}

auto PrintVisitor::visit(Delete* t_delete) -> void
{
  Printer printer{m_counter};

  printer.print("DELETE");
}

auto PrintVisitor::visit(Match* t_match) -> void
{
  Printer printer{m_counter};

  printer.print("MATCH");
}

auto PrintVisitor::visit(Not* t_not) -> void
{
  Printer printer{m_counter};

  printer.print("NOT");
  printer.print("| LEFT");
  t_not->left()->accept(this);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  Printer printer{m_counter};

  printer.print("AND");
  printer.print("| LEFT");
  t_and->left()->accept(this);

  printer.print("| RIGHT");
  t_and->right()->accept(this);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  Printer printer{m_counter};

  printer.print("OR");

  printer.print("| LEFT");
  t_or->left()->accept(this);

  printer.print("| right");
  t_or->right()->accept(this);
}

auto PrintVisitor::visit(StringConcatenation* t_conc) -> void
{
  Printer printer{m_counter};

  printer.print("STRING CONCATENATION");

  printer.print("| LEFT");
  t_conc->left()->accept(this);

  printer.print("| RIGHT");
  t_conc->right()->accept(this);
}

auto PrintVisitor::visit(Grouping* t_grouping) -> void
{
  Printer printer{m_counter};

  printer.print("GROUPING");
  if(auto& expr{t_grouping->left()}; expr) {
    printer.print("| EXPR");
    expr->accept(this);
  }
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  Printer printer{m_counter};

  printer.print("TERNARY");

  if(NodePtr & condition{t_ternary->condition()}; condition) {
    printer.print("| CONDITION");
    condition->accept(this);
  }

  if(NodePtr & then{t_ternary->then()}; then) {
    printer.print("| THEN");
    then->accept(this);
  }

  if(NodePtr & alt{t_ternary->alt()}; alt) {
    printer.print("| ELSE");
    alt->accept(this);
  }
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  Printer printer{m_counter};

  printer.print("UNARY PREFIX");
  // printer.print("| OP: ");

  // TODO: Implement plus or minus printing

  // Visit the unary expression
  t_unary_prefix->left()->accept(this);
}

auto PrintVisitor::visit(List* t_list) -> void
{
  Printer printer{m_counter};

  printer.print("LIST");

  for(NodePtr& node : *t_list)
    node->accept(this);
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  Printer printer{m_counter};

  printer.print("NIL");
}
