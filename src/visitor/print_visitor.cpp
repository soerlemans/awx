#include "print_visitor.hpp"


auto PrintVisitor::visit(node::control::If* t_if) -> void
{
  Printer printer{m_counter};

  printer.print("If");

  printer.print_if(t_if->then(), this, "| THEN");
}

auto PrintVisitor::visit(node::control::While* t_while) -> void
{
  Printer printer{m_counter};

  printer.print("While");
  printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(node::control::For* t_for) -> void
{
  Printer printer{m_counter};

  printer.print("For");
  // printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(node::control::ForIn* t_for) -> void
{
  Printer printer{m_counter};

  printer.print("FOR IN");
}

auto PrintVisitor::visit(node::control::Return* t_return) -> void
{
  Printer printer{m_counter};

  printer.print("RETURN");
}

auto PrintVisitor::visit(node::functions::Function* t_fn) -> void
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

auto PrintVisitor::visit(node::functions::FunctionCall* t_fn_call) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION CALL");
  printer.print("| NAME: ", t_fn_call->name());

  if(NodeListPtr & args{t_fn_call->args()}; args) {
    printer.print("| ARGS");
    args->accept(this);
  }
}

auto PrintVisitor::visit(node::functions::BuiltinFunction* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("BUILTIN FUNCTION CALL");
}

auto PrintVisitor::visit(node::recipes::SpecialPattern* t_pattern) -> void
{
  Printer printer{m_counter};

  printer.print("SPECIAL PATTERN");

  // TODO: List select special pattern
}

auto PrintVisitor::visit(node::recipes::Recipe* t_recipe) -> void
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

auto PrintVisitor::visit(node::io::Print* t_print) -> void
{
  Printer printer{m_counter};

  printer.print("PRINT");
  printer.print("| PARAMS:");

  visit(t_print->params().get());
}

auto PrintVisitor::visit(node::io::Printf* t_printf) -> void
{
  Printer printer{m_counter};

  printer.print("PRINTF");
  printer.print("| PARAMS:");

  visit(t_printf->params().get());
}

auto PrintVisitor::visit(node::io::Getline* t_getline) -> void
{
  Printer printer{m_counter};

  printer.print("GETLINE");
  if(NodePtr & var{t_getline->var()}; var) {
    printer.print("| VAR");
    var->accept(this);
  }
}

auto PrintVisitor::visit(node::io::Redirection* t_redirection) -> void
{
  Printer printer{m_counter};

  printer.print("REDIRECTION");
}

auto PrintVisitor::visit(node::lvalue::Array* t_array) -> void
{
  Printer printer{m_counter};

  printer.print("ARRAY");
}

auto PrintVisitor::visit(node::lvalue::FieldReference* t_fr) -> void
{
  Printer printer{m_counter};

  printer.print("FIELD REFERENCE");
  printer.print("| EXPR");

  t_fr->expr()->accept(this);
}

auto PrintVisitor::visit(node::lvalue::Variable* t_var) -> void
{
  Printer printer{m_counter};

  printer.print("VARIABLE");
  printer.print("| NAME: ", t_var->name());
}

auto PrintVisitor::visit(node::rvalue::Float* t_float) -> void
{
  Printer printer{m_counter};

  printer.print("FLOAT: ", t_float->get());
}

auto PrintVisitor::visit(node::rvalue::Integer* t_int) -> void
{
  Printer printer{m_counter};

  printer.print("INTEGER: ", t_int->get());
}

auto PrintVisitor::visit(node::rvalue::String* t_str) -> void
{
  Printer printer{m_counter};

  printer.print("STRING: ", t_str->get());
}

auto PrintVisitor::visit(node::rvalue::Regex* t_regex) -> void
{
  Printer printer{m_counter};

  printer.print("REGEX: ", t_regex->get());
}

auto PrintVisitor::visit(node::operators::Arithmetic* t_arithmetic) -> void
{
  Printer printer{m_counter};

  printer.print("ARITHMETIC");
}

auto PrintVisitor::visit(node::operators::Assignment* t_assignment) -> void
{
  Printer printer{m_counter};

  printer.print("ASSIGNMENT");
}

auto PrintVisitor::visit(node::operators::Comparison* t_comparison) -> void
{
  Printer printer{m_counter};

  printer.print("COMPARISON");
}

auto PrintVisitor::visit(node::operators::Increment* t_increment) -> void
{
  Printer printer{m_counter};

  printer.print("INCREMENT");
}

auto PrintVisitor::visit(node::operators::Decrement* t_decrement) -> void
{
  Printer printer{m_counter};

  printer.print("DECREMENT");
}

auto PrintVisitor::visit(node::operators::Delete* t_delete) -> void
{
  Printer printer{m_counter};

  printer.print("DELETE");
}

auto PrintVisitor::visit(node::operators::Match* t_match) -> void
{
  Printer printer{m_counter};

  printer.print("MATCH");
}

auto PrintVisitor::visit(node::operators::Not* t_not) -> void
{
  Printer printer{m_counter};

  printer.print("NOT");
  printer.print("| FIRST");
  t_not->first()->accept(this);
}

auto PrintVisitor::visit(node::operators::And* t_and) -> void
{
  Printer printer{m_counter};

  printer.print("AND");
  printer.print("| FIRST");
  t_and->first()->accept(this);

  printer.print("| SECOND");
  t_and->second()->accept(this);
}

auto PrintVisitor::visit(node::operators::Or* t_or) -> void
{
  Printer printer{m_counter};

  printer.print("OR");

  printer.print("| FIRST");
  t_or->first()->accept(this);

  printer.print("| SECOND");
  t_or->second()->accept(this);
}

auto PrintVisitor::visit(node::operators::StringConcatenation* t_conc) -> void
{
  Printer printer{m_counter};

  printer.print("STRING CONCATENATION");

  printer.print("| FIRST");
  t_conc->first()->accept(this);

  printer.print("| SECOND");
  t_conc->second()->accept(this);
}

auto PrintVisitor::visit(node::operators::Grouping* t_grouping) -> void
{
  Printer printer{m_counter};

  printer.print("GROUPING");
}

auto PrintVisitor::visit(node::operators::Ternary* t_ternary) -> void
{
  Printer printer{m_counter};

  printer.print("TERNARY");

  if(NodePtr & condition{t_ternary->first()}; condition) {
    printer.print("| CONDITION");
    condition->accept(this);
  }

  if(NodePtr & then{t_ternary->second()}; then) {
    printer.print("| THEN");
    then->accept(this);
  }

  if(NodePtr & third{t_ternary->third()}; third) {
    printer.print("| ELSE");
    third->accept(this);
  }
}

auto PrintVisitor::visit(node::operators::UnaryPrefix* t_unary_prefix) -> void
{
  Printer printer{m_counter};

  printer.print("UNARY PREFIX");
  printer.print("| OP: ", "IMPLEMENT");

  // Visit the unary expression
  t_unary_prefix->first()->accept(this);
}

auto PrintVisitor::visit(node::List* t_list) -> void
{
  Printer printer{m_counter};

  printer.print("LIST");

  for(NodePtr& node : *t_list)
    node->accept(this);
}

auto PrintVisitor::visit(node::Nil* t_nil) -> void
{
  Printer printer{m_counter};

  printer.print("NIL");
}
