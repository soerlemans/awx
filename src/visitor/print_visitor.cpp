#include "print_visitor.hpp"


auto PrintVisitor::visit(nodes::control::If* t_if) -> void
{
  Printer printer{m_counter};

  printer.print("If");

  printer.print_if(t_if->then(), this, "| THEN");
}

auto PrintVisitor::visit(nodes::control::While* t_while) -> void
{
  Printer printer{m_counter};

  printer.print("While");
  printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(nodes::control::For* t_for) -> void
{
  Printer printer{m_counter};

  printer.print("For");
  // printer.print_if(t_while->condition(), this, "| Condition");
  // printer.print_if(t_while->body(), this, "| Body");
}

auto PrintVisitor::visit(nodes::control::ForIn* t_for) -> void
{
  Printer printer{m_counter};

  printer.print("FOR IN");
}

auto PrintVisitor::visit(nodes::control::Return* t_return) -> void
{
  Printer printer{m_counter};

  printer.print("RETURN");
}

auto PrintVisitor::visit(nodes::functions::Function* t_fn) -> void
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

auto PrintVisitor::visit(nodes::functions::FunctionCall* t_fn_call) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION CALL");
  printer.print("| NAME: ", t_fn_call->name());

  if(NodeListPtr & args{t_fn_call->args()}; args) {
    printer.print("| ARGS");
    args->accept(this);
  }
}

auto PrintVisitor::visit(nodes::functions::BuiltinFunction* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("BUILTIN FUNCTION CALL");
}

auto PrintVisitor::visit(nodes::recipes::SpecialPattern* t_pattern) -> void
{
  Printer printer{m_counter};

  printer.print("SPECIAL PATTERN");

  // TODO: List select special pattern
}

auto PrintVisitor::visit(nodes::recipes::Recipe* t_recipe) -> void
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

auto PrintVisitor::visit(nodes::io::Print* t_print) -> void
{
  Printer printer{m_counter};

  printer.print("PRINT");
  printer.print("| PARAMS:");

  visit(t_print->params().get());
}

auto PrintVisitor::visit(nodes::io::Printf* t_printf) -> void
{
  Printer printer{m_counter};

  printer.print("PRINTF");
  printer.print("| PARAMS:");

  visit(t_printf->params().get());
}

auto PrintVisitor::visit(nodes::io::Getline* t_getline) -> void
{
  Printer printer{m_counter};

  printer.print("GETLINE");
  if(NodePtr & var{t_getline->var()}; var) {
    printer.print("| VAR");
    var->accept(this);
  }
}

auto PrintVisitor::visit(nodes::io::Redirection* t_redirection) -> void
{
  Printer printer{m_counter};

  printer.print("REDIRECTION");
}

auto PrintVisitor::visit(nodes::lvalue::Array* t_array) -> void
{
  Printer printer{m_counter};

  printer.print("ARRAY");
}

auto PrintVisitor::visit(nodes::lvalue::FieldReference* t_fr) -> void
{
  Printer printer{m_counter};

  printer.print("FIELD REFERENCE");
  printer.print("| EXPR");

  t_fr->expr()->accept(this);
}

auto PrintVisitor::visit(nodes::lvalue::Variable* t_var) -> void
{
  Printer printer{m_counter};

  printer.print("VARIABLE");
  printer.print("| NAME: ", t_var->name());
}

auto PrintVisitor::visit(nodes::rvalue::Float* t_float) -> void
{
  Printer printer{m_counter};

  printer.print("FLOAT: ", t_float->get());
}

auto PrintVisitor::visit(nodes::rvalue::Integer* t_int) -> void
{
  Printer printer{m_counter};

  printer.print("INTEGER: ", t_int->get());
}

auto PrintVisitor::visit(nodes::rvalue::String* t_str) -> void
{
  Printer printer{m_counter};

  printer.print("STRING: ", t_str->get());
}

auto PrintVisitor::visit(nodes::rvalue::Regex* t_regex) -> void
{
  Printer printer{m_counter};

  printer.print("REGEX: ", t_regex->get());
}

auto PrintVisitor::visit(nodes::operators::Arithmetic* t_arithmetic) -> void
{
  Printer printer{m_counter};

  printer.print("ARITHMETIC");
}

auto PrintVisitor::visit(nodes::operators::Assignment* t_assignment) -> void
{
  Printer printer{m_counter};

  printer.print("ASSIGNMENT");
}

auto PrintVisitor::visit(nodes::operators::Comparison* t_comparison) -> void
{
  Printer printer{m_counter};

  printer.print("COMPARISON");
}

auto PrintVisitor::visit(nodes::operators::Increment* t_increment) -> void
{
  Printer printer{m_counter};

  printer.print("INCREMENT");
}

auto PrintVisitor::visit(nodes::operators::Decrement* t_decrement) -> void
{
  Printer printer{m_counter};

  printer.print("DECREMENT");
}

auto PrintVisitor::visit(nodes::operators::Delete* t_delete) -> void
{
  Printer printer{m_counter};

  printer.print("DELETE");
}

auto PrintVisitor::visit(nodes::operators::Match* t_match) -> void
{
  Printer printer{m_counter};

  printer.print("MATCH");
}

auto PrintVisitor::visit(nodes::operators::Not* t_not) -> void
{
  Printer printer{m_counter};

  printer.print("NOT");
  printer.print("| FIRST");
  t_not->first()->accept(this);
}

auto PrintVisitor::visit(nodes::operators::And* t_and) -> void
{
  Printer printer{m_counter};

  printer.print("AND");
  printer.print("| FIRST");
  t_and->first()->accept(this);

  printer.print("| SECOND");
  t_and->second()->accept(this);
}

auto PrintVisitor::visit(nodes::operators::Or* t_or) -> void
{
  Printer printer{m_counter};

  printer.print("OR");

  printer.print("| FIRST");
  t_or->first()->accept(this);

  printer.print("| SECOND");
  t_or->second()->accept(this);
}

auto PrintVisitor::visit(nodes::operators::StringConcatenation* t_conc) -> void
{
  Printer printer{m_counter};

  printer.print("STRING CONCATENATION");

  printer.print("| FIRST");
  t_conc->first()->accept(this);

  printer.print("| SECOND");
  t_conc->second()->accept(this);
}

auto PrintVisitor::visit(nodes::operators::Ternary* t_ternary) -> void
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

auto PrintVisitor::visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void
{
  Printer printer{m_counter};

  printer.print("UNARY PREFIX");
  printer.print("| OP: ", "IMPLEMENT");

  // Visit the unary expression
  t_unary_prefix->first()->accept(this);
}

auto PrintVisitor::visit(nodes::List* t_list) -> void
{
  Printer printer{m_counter};

  printer.print("LIST");

  for(NodePtr& node : *t_list)
    node->accept(this);
}

auto PrintVisitor::visit(nodes::Nil* t_nil) -> void
{
  Printer printer{m_counter};

  printer.print("NIL");
}
