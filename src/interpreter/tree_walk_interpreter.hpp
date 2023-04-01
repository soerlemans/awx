#ifndef TREE_WALK_INTERPRETER_HPP
#define TREE_WALK_INTERPRETER_HPP

// STL Includes:
#include <map>
#include <variant>

// Local Includes:
#include "node_visitor.hpp"


namespace visitor {
/*! Evaluates each node and returns a result
 * TODO: Have NodeVisitor be a template class and have each Node accept a
 * pointer to NodeVisitor<T> this way we can
 */
class TreeWalkInterpreter : public NodeVisitor {
  private:
  template<typename T>
  using Store = std::map<std::string, T>;
  using Any = std::variant<double, std::string>;
  // using Array = std::map<Any, Any>;

  //! Context contains the result of
  struct Context {
    // Sometimes we need the name of a variable or function
    std::string m_name;
    Any m_result;
  } m_context;

  Store<Any> m_variables;
  Store<node::NodePtr> m_functions;

  public:
  TreeWalkInterpreter() = default;

  //! Walk returns the updated context
  auto walk(node::NodePtr t_node) -> Context&;

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

  ~TreeWalkInterpreter() override = default;
};
} // namespace visitor

#endif // TREE_WALK_INTERPRETER_HPP
