#ifndef EVALUATE_VISITOR_HPP
#define EVALUATE_VISITOR_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "node_visitor.hpp"


class EvaluateVisitor : public NodeVisitor {
  private:
  std::variant<int> m_result;

  public:
  EvaluateVisitor() = default;

  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::While* t_while) -> void override;
  auto visit(node::control::For* t_for) -> void override;
  auto visit(node::control::ForIn* t_for) -> void override;
  auto visit(node::control::Return* t_return) -> void override;

  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(node::functions::BuiltinFunction* t_fn) -> void override;

  auto visit(node::recipes::SpecialPattern* t_pattern) -> void override;
  auto visit(node::recipes::Recipe* t_recipe) -> void override;

  auto visit(node::io::Print* t_print) -> void override;
  auto visit(node::io::Printf* t_printf) -> void override;
  auto visit(node::io::Getline* t_getline) -> void override;
  auto visit(node::io::Redirection* t_redirection) -> void override;

  auto visit(node::lvalue::Array* t_array) -> void override;
  auto visit(node::lvalue::FieldReference* t_fr) -> void override;
  auto visit(node::lvalue::Variable* t_var) -> void override;

  auto visit(node::rvalue::Float* t_float) -> void override;
  auto visit(node::rvalue::Integer* t_int) -> void override;
  auto visit(node::rvalue::String* t_str) -> void override;
  auto visit(node::rvalue::Regex* t_regex) -> void override;

  auto visit(node::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(node::operators::Assignment* t_assignment) -> void override;
  auto visit(node::operators::Comparison* t_comparison) -> void override;

  auto visit(node::operators::Increment* t_increment) -> void override;
  auto visit(node::operators::Decrement* t_decrement) -> void override;

  auto visit(node::operators::Delete* t_delete) -> void override;
  auto visit(node::operators::Match* t_match) -> void override;

  auto visit(node::operators::Not* t_not) -> void override;
  auto visit(node::operators::And* t_and) -> void override;
  auto visit(node::operators::Or* t_or) -> void override;

  auto visit(node::operators::StringConcatenation* t_conc) -> void override;
  auto visit(node::operators::Grouping* t_grouping) -> void override;
  auto visit(node::operators::Ternary* t_ternary) -> void override;

  auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void override;

  auto visit(node::List* t_list) -> void override;
  auto visit(node::Nil* t_nil) -> void override;

  ~EvaluateVisitor() override = default;
};

#endif // EVALUATE_VISITOR_HPP
