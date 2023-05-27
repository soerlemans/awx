#ifndef AWX_VISITOR_NODE_VISITOR_HPP
#define AWX_VISITOR_NODE_VISITOR_HPP

// Includes:
#include "../node/node.hpp"


namespace visitor {
/*! Implementation of the Visitor design pattern for Nodes
 * This creates a recursive dependency on the different kind of nodes
 * So all nodes need to be forward declared in this header
 */
class NodeVisitor {
  private:
  public:
  NodeVisitor() = default;

  virtual auto visit(node::control::If* t_if) -> void = 0;
  virtual auto visit(node::control::While* t_while) -> void = 0;
  virtual auto visit(node::control::DoWhile* t_do_while) -> void = 0;
  virtual auto visit(node::control::For* t_for) -> void = 0;
  virtual auto visit(node::control::ForIn* t_for_in) -> void = 0;
  virtual auto visit(node::control::Continue* t_continue) -> void = 0;
  virtual auto visit(node::control::Break* t_break) -> void = 0;
  virtual auto visit(node::control::Next* t_next) -> void = 0;
  virtual auto visit(node::control::Exit* t_exit) -> void = 0;
  virtual auto visit(node::control::Return* t_return) -> void = 0;

  virtual auto visit(node::functions::Function* t_fn) -> void = 0;
  virtual auto visit(node::functions::FunctionCall* t_fn_call) -> void = 0;
  virtual auto visit(node::functions::BuiltinFunctionCall* t_fn) -> void = 0;

  virtual auto visit(node::recipes::SpecialPattern* t_pattern) -> void = 0;
  virtual auto visit(node::recipes::Recipe* t_recipe) -> void = 0;

  virtual auto visit(node::io::Print* t_print) -> void = 0;
  virtual auto visit(node::io::Printf* t_printf) -> void = 0;
  virtual auto visit(node::io::Getline* t_getline) -> void = 0;
  virtual auto visit(node::io::Redirection* t_redirection) -> void = 0;

  virtual auto visit(node::lvalue::Array* t_array) -> void = 0;
  virtual auto visit(node::lvalue::FieldReference* t_fr) -> void = 0;
  virtual auto visit(node::lvalue::Variable* t_var) -> void = 0;

  virtual auto visit(node::rvalue::Float* t_float) -> void = 0;
  virtual auto visit(node::rvalue::Integer* t_int) -> void = 0;
  virtual auto visit(node::rvalue::String* t_str) -> void = 0;
  virtual auto visit(node::rvalue::Regex* t_regex) -> void = 0;

  virtual auto visit(node::operators::Arithmetic* t_arithmetic) -> void = 0;
  virtual auto visit(node::operators::Assignment* t_assignment) -> void = 0;
  virtual auto visit(node::operators::Comparison* t_comparison) -> void = 0;

  virtual auto visit(node::operators::Increment* t_increment) -> void = 0;
  virtual auto visit(node::operators::Decrement* t_decrement) -> void = 0;

  virtual auto visit(node::operators::Delete* t_delete) -> void = 0;
  virtual auto visit(node::operators::Match* t_match) -> void = 0;

  virtual auto visit(node::operators::Not* t_not) -> void = 0;
  virtual auto visit(node::operators::And* t_and) -> void = 0;
  virtual auto visit(node::operators::Or* t_or) -> void = 0;

  virtual auto visit(node::operators::StringConcatenation* t_conc) -> void = 0;
  virtual auto visit(node::operators::Grouping* t_grouping) -> void = 0;
  virtual auto visit(node::operators::Ternary* t_ternary) -> void = 0;

  virtual auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void = 0;

  virtual auto visit(node::List* t_list) -> void = 0;
  virtual auto visit(node::Nil* t_nil) -> void = 0;

  virtual auto visit(node::NodeInterface* t_node) -> void;

  virtual ~NodeVisitor() = default;
};
} // namespace visitor

#endif // AWX_VISITOR_NODE_VISITOR_HPP
