#include "print_visitor.hpp"


PrintVisitor::PrintVisitor()
{}

auto PrintVisitor::visit(nodes::control::If* t_if) -> void
{}

auto PrintVisitor::visit(nodes::functions::Function* t_fn) -> void
{}

auto PrintVisitor::visit(nodes::functions::FunctionCall* t_fn_call) -> void
{}

auto PrintVisitor::visit(nodes::functions::BuiltinFunction* t_fn) -> void
{}

auto PrintVisitor::visit(nodes::io::Print* t_print) -> void
{}

auto PrintVisitor::visit(nodes::io::Printf* t_printf) -> void
{}

auto PrintVisitor::visit(nodes::io::Getline* t_getline) -> void
{}

auto PrintVisitor::visit(nodes::io::Redirection* t_redirection) -> void
{}

auto PrintVisitor::visit(nodes::lvalue::Array* t_array) -> void
{}

auto PrintVisitor::visit(nodes::lvalue::FieldReference* t_fr) -> void
{}

auto PrintVisitor::visit(nodes::lvalue::Variable* t_var) -> void
{}

auto PrintVisitor::visit(nodes::rvalue::Float* t_float) -> void
{}

auto PrintVisitor::visit(nodes::rvalue::Integer* t_int) -> void
{}

auto PrintVisitor::visit(nodes::rvalue::String* t_str) -> void
{}

auto PrintVisitor::visit(nodes::operators::Arithmetic* t_arithmetic) -> void
{}

auto PrintVisitor::visit(nodes::operators::Assignment* t_assignment) -> void
{}

auto PrintVisitor::visit(nodes::operators::Comparison* t_comparison) -> void
{}

auto PrintVisitor::visit(nodes::operators::Increment* t_increment) -> void
{}

auto PrintVisitor::visit(nodes::operators::Decrement* t_decrement) -> void
{}

auto PrintVisitor::visit(nodes::operators::Delete* t_delete) -> void
{}

auto PrintVisitor::visit(nodes::operators::Ere* t_ere) -> void
{}

auto PrintVisitor::visit(nodes::operators::Not* t_ere) -> void
{}

auto PrintVisitor::visit(nodes::operators::And* t_and) -> void
{}

auto PrintVisitor::visit(nodes::operators::Or* t_or) -> void
{}

auto PrintVisitor::visit(nodes::operators::StringConcatenation* t_conc) -> void
{}

auto PrintVisitor::visit(nodes::operators::Ternary* t_ternary) -> void
{}

auto PrintVisitor::visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void
{}

auto PrintVisitor::visit(nodes::List* t_list) -> void
{}

PrintVisitor::~PrintVisitor()
{}
