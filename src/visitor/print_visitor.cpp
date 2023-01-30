#include "print_visitor.hpp"


PrintVisitor::PrintVisitor(): m_counter{0}
{}

auto PrintVisitor::visit(nodes::control::If* t_if) -> void
{
  Printer printer{m_counter};

  printer.print("IF");
}

auto PrintVisitor::visit(nodes::functions::Function* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION");
}

auto PrintVisitor::visit(nodes::functions::FunctionCall* t_fn_call) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION CALL");
}

auto PrintVisitor::visit(nodes::functions::BuiltinFunction* t_fn) -> void
{
  Printer printer{m_counter};

  printer.print("FUNCTION CALL");
}

auto PrintVisitor::visit(nodes::io::Print* t_print) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::io::Printf* t_printf) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::io::Getline* t_getline) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::io::Redirection* t_redirection) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::lvalue::Array* t_array) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::lvalue::FieldReference* t_fr) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::lvalue::Variable* t_var) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::rvalue::Float* t_float) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::rvalue::Integer* t_int) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::rvalue::String* t_str) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Arithmetic* t_arithmetic) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Assignment* t_assignment) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Comparison* t_comparison) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Increment* t_increment) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Decrement* t_decrement) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Delete* t_delete) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Ere* t_ere) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Not* t_ere) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::And* t_and) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Or* t_or) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::StringConcatenation* t_conc) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::Ternary* t_ternary) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

auto PrintVisitor::visit(nodes::List* t_list) -> void
{
  Printer printer{m_counter};

  printer.print("IMPLEMENT");
}

PrintVisitor::~PrintVisitor()
{}
