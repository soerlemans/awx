#include "print_visitor.hpp"

#include "../node/list.hpp"
#include "../node/node.hpp"

#include "../node/io/getline.hpp"
#include "../node/io/print.hpp"
#include "../node/io/printf.hpp"
#include "../node/io/redirection.hpp"

#include "../node/rvalue/literal.hpp"
#include "../node/rvalue/rvalue.hpp"

#include "../node/lvalue/array.hpp"
#include "../node/lvalue/field_reference.hpp"
#include "../node/lvalue/variable.hpp"

#include "../node/functions/function.hpp"
#include "../node/functions/function_call.hpp"

#include "../node/operators/arithmetic.hpp"
#include "../node/operators/assignment.hpp"
#include "../node/operators/comparison.hpp"
#include "../node/operators/decrement.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"
#include "../node/operators/string_concatenation.hpp"
#include "../node/operators/unary_prefix.hpp"


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

  printer.print("BUILTIN FUNCTION CALL");
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
}

auto PrintVisitor::visit(nodes::io::Redirection* t_redirection) -> void
{
  Printer printer{m_counter};

  printer.print("REDIRECTION");
}

auto PrintVisitor::visit(nodes::lvalue::Array* t_array) -> void
{
  Printer printer{m_counter};

  printer.print("Array");
}

auto PrintVisitor::visit(nodes::lvalue::FieldReference* t_fr) -> void
{
  Printer printer{m_counter};

  printer.print("FIELD REFERENCE");
}

auto PrintVisitor::visit(nodes::lvalue::Variable* t_var) -> void
{
  Printer printer{m_counter};

  printer.print("VARIABLE");
}

auto PrintVisitor::visit(nodes::rvalue::Float* t_float) -> void
{
  Printer printer{m_counter};

  printer.print("FLOAT");
  printer.print("| ", t_float->get());
}

auto PrintVisitor::visit(nodes::rvalue::Integer* t_int) -> void
{
  Printer printer{m_counter};

  printer.print("INTEGER");
  printer.print("| ", t_int->get());
}

auto PrintVisitor::visit(nodes::rvalue::String* t_str) -> void
{
  Printer printer{m_counter};

  printer.print("STRING");
  printer.print("| ", t_str->get());
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

auto PrintVisitor::visit(nodes::operators::Ere* t_ere) -> void
{
  Printer printer{m_counter};

  printer.print("ERE");
}

auto PrintVisitor::visit(nodes::operators::Not* t_not) -> void
{
  Printer printer{m_counter};

  printer.print("NOT");
}

auto PrintVisitor::visit(nodes::operators::And* t_and) -> void
{
  Printer printer{m_counter};

  printer.print("AND");
}

auto PrintVisitor::visit(nodes::operators::Or* t_or) -> void
{
  Printer printer{m_counter};

  printer.print("OR");
}

auto PrintVisitor::visit(nodes::operators::StringConcatenation* t_conc) -> void
{
  Printer printer{m_counter};

  printer.print("STRING CONCATENATION");
}

auto PrintVisitor::visit(nodes::operators::Ternary* t_ternary) -> void
{
  Printer printer{m_counter};

  printer.print("TERNARY");
}

auto PrintVisitor::visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void
{
  Printer printer{m_counter};

  printer.print("UNARY PREFIX");
}

auto PrintVisitor::visit(nodes::List* t_list) -> void
{
  Printer printer{m_counter};

  printer.print("LIST");

  for(NodePtr& node : *t_list)
    node->accept(this);
}

PrintVisitor::~PrintVisitor()
{}
