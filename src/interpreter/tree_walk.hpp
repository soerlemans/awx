#ifndef TREE_WALK_HPP
#define TREE_WALK_HPP

// STL Includes:
#include <map>
#include <stack>
#include <variant>

// Includes:
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "context.hpp"
#include "return_exception.hpp"


namespace interpreter {
/*! Evaluates each node and returns a result
 * TODO: Have NodeVisitor be a template class and have each Node accept a
 * pointer to NodeVisitor<T> this way we can
 */
class TreeWalkInterpreter : public visitor::NodeVisitor {
  private:
  template<typename T>
  using Store = std::map<std::string, T>;

  // Store<Any> m_local_scope;
  Store<Any> m_globals;
  std::stack<Store<Any>> m_scope;
  Store<node::functions::NodeFuncPtr> m_functions;

  //! Context gets set when an expression is evaluated
  Context m_context;

  public:
  TreeWalkInterpreter() = default;

  //! Walk returns the updated context
  auto walk(node::NodePtr t_node) -> Context&;
  auto eval_bool(node::NodePtr t_node) -> bool;
  auto double2str(double t_number) -> std::string;

  auto clear_context() -> void;

  auto set_variable(std::string t_name, Any t_variable) -> void;
  auto get_variable(const std::string t_name) -> Any&;

  // Visit Methods:
  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::While* t_while) -> void override;
  auto visit(node::control::For* t_for) -> void override;
  auto visit(node::control::ForIn* t_for) -> void override;
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

  ~TreeWalkInterpreter() override = default;
};
} // namespace interpreter

#endif // TREE_WALK_HPP
