#ifndef AWX_INTERPRETER_TREE_WALK_TREE_WALK_HPP
#define AWX_INTERPRETER_TREE_WALK_TREE_WALK_HPP

// STL Includes:
#include <map>
#include <stack>
#include <variant>

// Includes:
#include "../../container/file_buffer.hpp"
#include "../../visitor/node_visitor.hpp"
#include "../context.hpp"
#include "../field_store.hpp"

// Local Includes:
#include "control.hpp"


namespace interpreter::tree_walk {
/*! Evaluates each node using the visitor pattern.
 */
class TreeWalk : public visitor::NodeVisitor {
  private:
  // Aliases:
  template<typename T>
  using Store = std::map<std::string, T>;

  // Members:
  node::NodePtr m_ast;
  std::size_t m_nr;

  // Runtime environment variables:
  Store<Any> m_globals;
  std::stack<Store<Any>> m_scope;
  Store<node::functions::NodeFuncPtr> m_functions;

  // Context gets set when an expression is evaluated
  Context m_context;

  // In certain contexts extended regular expression literal should not be
  // resolved
  bool m_resolve;

  FieldStore m_fields;

  public:
  TreeWalk(node::NodePtr t_ast, const container::TextBufferPtr& t_input);

  //! Walk returns the updated context
  auto walk(node::NodePtr t_node) -> Context&;
  auto eval_bool(node::NodePtr t_node) -> bool;
  auto double2str(double t_number) -> std::string;

  auto clear_context() -> void;

  auto set(std::string t_name, Any t_variable) -> void;
  auto get(const std::string t_name) -> Any&;

  // Visit Methods:
  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::While* t_while) -> void override;
  auto visit(node::control::DoWhile* t_do_while) -> void override;
  auto visit(node::control::For* t_for) -> void override;
  auto visit(node::control::ForIn* t_for_in) -> void override;
  auto visit(node::control::Continue* t_continue) -> void override;
  auto visit(node::control::Break* t_break) -> void override;
  auto visit(node::control::Next* t_next) -> void override;
  auto visit(node::control::Exit* t_exit) -> void override;
  auto visit(node::control::Return* t_return) -> void override;

  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(node::functions::BuiltinFunctionCall* t_fn) -> void override;

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

  // Runtime methods:
  auto init(const container::TextBufferPtr& t_input) -> void;
  auto update(const container::TextBufferPtr& t_input) -> void;
  auto run(const container::TextBufferPtr& t_input) -> void;

  ~TreeWalk() override = default;
};
} // namespace interpreter::tree_walk

#endif // AWX_INTERPRETER_TREE_WALK_TREE_WALK_HPP
